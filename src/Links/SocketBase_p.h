/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <fmt/format.h>
#include <mongoose.h>
#include <wx/wx.h>

#include "Link_p.h"
#include "SocketBase.h"

void DoMgPoll(struct mg_connection *c, int ev, void *ev_data);

class SocketBasePrivate : public LinkPrivate
{
public:
    SocketBasePrivate()
        : LinkPrivate()
        , isEnableAuthorization(false)
        , dataChannel(0)
    {}

    wxString clientAddress;
    uint16_t clientPort;
    wxString serverAddress;
    uint16_t serverPort;

    // The members for web socket
    bool isEnableAuthorization;
    int dataChannel;
    wxString userName;
    wxString password;

public:
#if 0
    void OnMgEvOpen(struct mg_connection *c)
    {
        const std::string locIp = DoMgAddressToIpV4(&c->loc);
        const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
        const std::string remIp = DoMgAddressToIpV4(&c->rem);
        const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);

        wxtInfo() << fmt::format("Socket opened local({0}:{1}), remote({2}:{3}).",
                                 locIp,
                                 locPort,
                                 remIp,
                                 remPort);
        DoQueueLinkOpened();
    }

    void OnMgEvRead(struct mg_connection *c)
    {
        if (c->recv.len <= 0) {
            return;
        }

        wxtDataItem item;
        item.len = c->recv.len;

        const std::string ip = DoMgAddressToIpV4(&c->rem);
        const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
        const std::string from = DoEncodeFlag(ip, port);
        item.flag = from;

        std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
        memcpy(bytes.get(), c->recv.buf, c->recv.len);
        item.data = bytes;
        DoQueueTxBytes(bytes, c->recv.len, from);
        c->recv.len = 0;
    }

    void OnMgEvClose(struct mg_connection *c)
    {
        DoQueueError(GetStrServerClosed());
        DoQueueLinkClosed();
    }

    void OnMgEvError(struct mg_connection *c, void *ev_data)
    {
        if (evtHandler) {
            if (GetIsClient()) {
                std::string msg = reinterpret_cast<const char *>(ev_data);
                DoQueueError(msg);
            } else {
                if (c->is_client) {
                    std::string ip = DoMgAddressToIpV4(&c->rem);
                    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
                    std::string to = DoEncodeFlag(ip, port);
                    wxtInfo() << fmt::format("Socket({0}) error.", to);
                } else {
                    std::string msg = reinterpret_cast<const char *>(ev_data);
                    DoQueueError(msg);
                }
            }
        }
    }

    void OnMgEvPoll(struct mg_connection *c, void *ev_data)
    {
        txBytesLock.lock();
        for (auto &ctx : txBytes) {
            if (mg_send(c, ctx.first.get(), ctx.second)) {
                std::string ip = DoMgAddressToIpV4(&c->rem);
                uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
                std::string to = DoEncodeFlag(ip, port);
                DoQueueTxBytes(ctx.first, ctx.second, to);
            } else {
                DoQueueError(_("Client write bytes failed."));
                break;
            }
        }

        txBytes.clear();
        txBytesLock.unlock();
    }
#endif
public:
    // clang-format off
    virtual std::string GetProtocolName() const = 0;
    virtual mg_connection *DoConnection(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn) = 0;
    virtual bool GetIsClient() const = 0;
    // clang-format on
    virtual void DoPoll(struct mg_connection *c, int ev, void *ev_data) {};

    void Poll() override
    {
        std::string url = fmt::format("{0}://{1}:{2}",
                                      GetProtocolName(),
                                      serverAddress.ToStdString(),
                                      serverPort);
        struct mg_mgr mgr;
        mg_mgr_init(&mgr);
        mgr.userdata = this;
        auto c = DoConnection(&mgr, url.c_str(), DoMgPoll);
        if (c == nullptr) {
            mg_mgr_free(&mgr);
            DoQueueError(_("Open socket failed, please check parameters then try again."));
            return;
        }

        c->is_client = GetIsClient();
        auto q = GetQ<SocketBase *>();
        while (!q->TestDestroy()) {
            mg_mgr_poll(&mgr, 100);
        }

        mg_mgr_free(&mgr);
    }

public:
    std::string DoMgAddressToIpV4(const struct mg_addr *addr)
    {
        if (addr == nullptr) {
            return std::string("0.0.0.0");
        }

        char ipv4[4] = {0};
        memcpy(ipv4, addr->ip, 4);
        std::string ip;
        for (int i = 0; i < 4; i++) {
            ip += std::to_string(static_cast<uint8_t>(ipv4[i]));
            if (i < 3) {
                ip += ".";
            }
        }

        return ip;
    }

    bool DoIpV4ToMgAddress(const std::string &ip, struct mg_addr *addr)
    {
        if (addr == nullptr) {
            return false;
        }

        // split the ip address by '.'
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(ip);
        while (std::getline(tokenStream, token, '.')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 4) {
            return false;
        }

        for (int i = 0; i < 4; i++) {
            addr->ip[i] = static_cast<uint8_t>(std::stoi(tokens[i]));
        }

        return true;
    }

    const wxString GetStrUnconnected() { return _("Unconnected"); }

    const wxString GetStrClientClosed()
    {
        return _("Client closed, server has been closed or not found.");
    }

    const wxString GetStrServerClosed() { return _("Server has been closed."); }

    const wxString GetStrFailedToCreateServer()
    {
        return _("Failed to create server, please check parameters then try again.");
    }
};

static void DoMgPoll(struct mg_connection *c, int ev, void *ev_data)
{
    auto d = reinterpret_cast<SocketBasePrivate *>(c->mgr->userdata);
    if (!d) {
        wxtWarning() << "SocketBasePrivate pointer is null.";
        return;
    }

    d->DoPoll(c, ev, ev_data);
}
