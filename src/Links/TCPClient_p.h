/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <fmt/format.h>

#include "SocketClient_p.h"
#include "TCPClient.h"

class TCPClientPrivate : public SocketClientPrivate
{
public:
    std::string GetProtocolName() const override { return std::string("tcp"); }
    mg_connection *DoConnection(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn) override
    {
        return mg_connect(mgr, url, fn, nullptr);
    }
    bool GetIsClient() const override { return true; }

public:
    void DoPoll(struct mg_connection *c, int ev, void *ev_data) override
    {
        SocketClientPrivate::DoPoll(c, ev, ev_data);
    }
};
#if 0
static void OnMgEvRead(struct mg_connection *c, void *ev_data, TCPClient *q)
{
    if (c->recv.len <= 0) {
        return;
    }

    auto *d = q->GetD<TCPClientPrivate *>();
    const std::string ip = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string from = DoEncodeFlag(ip, port);

    std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), c->recv.buf, c->recv.len);

    d->DoQueueRxBytes(bytes, c->recv.len, from);
    c->recv.len = 0;
}

static void OnMgEvPoll(struct mg_connection *c, void *ev_data, TCPClient *q)
{
    auto *d = q->GetD<SocketClientPrivate *>();
    size_t len = 0;
    std::string ip = d->DoMgAddressToIpV4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string to = DoEncodeFlag(ip, port);

    for (auto &ctx : d->txBytes) {
        if (mg_send(c, ctx.first.get(), ctx.second)) {
            d->DoQueueTxBytes(ctx.first, ctx.second, to);
        } else {
            d->DoQueueError(_("TCP client send bytes error."));
            break;
        }
    }

    d->txBytes.clear();
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, TCPClient *q)
{
    wxUnusedVar(c);
    wxUnusedVar(ev_data);

    auto *d = q->GetD<SocketClientPrivate *>();
    d->DoQueueError(d->GetStrClientClosed());
    d->DoQueueLinkClosed();
}

static void OnMgEvConnect(struct mg_connection *c, void *ev_data, TCPClient *q)
{
    wxUnusedVar(c);
    wxUnusedVar(ev_data);

    auto *d = q->GetD<SocketClientPrivate *>();
    d->DoQueueLinkOpened();
}

static void TCPClientHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto *q = reinterpret_cast<TCPClient *>(c->mgr->userdata);
    wxASSERT_MSG(q, "q is nullptr");

    if (ev == MG_EV_READ) {
        OnMgEvRead(c, ev_data, q);
    } else if (ev == MG_EV_POLL) {
        OnMgEvPoll(c, ev_data, q);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    } else if (ev == MG_EV_CONNECT) {
        OnMgEvConnect(c, ev_data, q);
    }
}
#endif
