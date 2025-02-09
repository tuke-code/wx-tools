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
    // clang-format off
    virtual std::string GetProtocolName() const = 0;
    virtual mg_connection *DoConnection(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn) = 0;
    virtual bool GetIsClient() const = 0;
    virtual void DoPoll(struct mg_connection *c, int ev, void *ev_data);
    // clang-format on

    void Poll() override
    {
        std::string url = fmt::format("{0}://{1}{2}",
                                      GetProtocolName(),
                                      serverAddress.ToStdString(),
                                      serverPort);
        struct mg_mgr mgr;
        mg_mgr_init(&mgr);
        mgr.userdata = this;
        auto c = DoConnection(&mgr, url.c_str(), &DoMgPoll);
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
    auto q = reinterpret_cast<SocketBase *>(c->mgr->userdata);
    if (!q) {
        return;
    }

    auto d = q->GetD<SocketBasePrivate *>();
    d->DoPoll(c, ev, ev_data);
}
