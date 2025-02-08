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

#include "Common/wxTools.h"
#include "Links/WSClient.h"
#include "SocketClient_p.h"

class WSClientPrivate : public SocketClientPrivate
{
public:
};

static void OnMgEvWsOpen(struct mg_connection *c, void *ev_data, WSClient *q)
{
    c->is_hexdumping = 1;

    auto *d = q->GetD<WSClientPrivate>();
    const std::string locIp = d->DoMgAddressToIpV4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string remIp = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);

    std::string loc = fmt::format("{0}:{1}", locIp, locPort);
    std::string rem = fmt::format("{0}:{1}", remIp, remPort);
    wxtInfo() << fmt::format("WebSocket client({0}) has been connected to {1}", loc, rem);
}

static void OnMgEvWsMsg(struct mg_connection *c, void *ev_data, WSClient *q)
{
    struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
    std::string op;
    if ((wm->flags & WEBSOCKET_OP_TEXT) == WEBSOCKET_OP_TEXT) {
        op = std::string("(T)");
    } else if ((wm->flags & WEBSOCKET_OP_BINARY) == WEBSOCKET_OP_BINARY) {
        op = std::string("(B)");
    } else {
        wxtWarning() << "Unknown data channel: " << wm->flags;
        return;
    }

    auto *d = q->GetD<WSClientPrivate>();
    std::string ip = q->GetD<WSClientPrivate>()->DoMgAddressToIpV4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string from = DoEncodeFlag(ip, port) + op;
    std::shared_ptr<char> bytes(new char[wm->data.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), wm->data.buf, wm->data.len);
    d->DoQueueRxBytes(bytes, wm->data.len, from);
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();
    const std::string locIp = d->DoMgAddressToIpV4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string remIp = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);

    std::string loc = fmt::format("{0}:{1}", locIp, locPort);
    std::string rem = fmt::format("{0}:{1}", remIp, remPort);
    wxtInfo() << fmt::format("WebSocket client({0}) has been disconnected from {1}", loc, rem);

    d->DoQueueError(_("WebSocket client has been close."));
}

static void OnMgEvError(struct mg_connection *c, void *ev_data, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();
    d->DoQueueError(wxString(reinterpret_cast<char *>(ev_data)));
}

static void OnMgEvPoll(struct mg_connection *c, int ev, void *ev_data, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();
    std::string op;
    size_t len = 0;
    std::string ip = d->DoMgAddressToIpV4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string to = DoEncodeFlag(ip, port);

    d->txBytesLock.lock();
    for (auto &ctx : d->txBytes) {
        if (d->dataChannel == WEBSOCKET_OP_TEXT) {
            op = std::string("(T)");
            len = mg_ws_send(c, ctx.first.get(), ctx.second, WEBSOCKET_OP_TEXT);
        } else {
            op = std::string("(B)");
            len = mg_ws_send(c, ctx.first.get(), ctx.second, WEBSOCKET_OP_BINARY);
        }

        if (len > 0) {
            d->DoQueueTxBytes(ctx.first, ctx.second, to + op);
        } else {
            d->DoQueueError(_("WS server send bytes error."));
            break;
        }
    }

    d->txBytes.clear();
    d->txBytesLock.unlock();
}

static void WSClientHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto q = reinterpret_cast<WSClient *>(c->mgr->userdata);
    if (ev == MG_EV_WS_OPEN) {
        OnMgEvWsOpen(c, ev_data, q);
    } else if (ev == MG_EV_WS_MSG) {
        OnMgEvWsMsg(c, ev_data, q);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    } else if (ev == MG_EV_ERROR) {
        OnMgEvError(c, ev_data, q);
    } else if (ev == MG_EV_POLL) {
        OnMgEvPoll(c, ev, ev_data, q);
    }
}
