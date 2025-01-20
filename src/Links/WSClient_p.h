/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <mongoose.h>

#include "Common/wxTools.h"
#include "Links/WSClient.h"
#include "SocketClient_p.h"

class WSClientPrivate : public SocketClientPrivate
{
public:
};

static void DoSendBytesToClient(struct mg_connection *c, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();
    std::string op;
    size_t len = 0;
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string to = DoEncodeFlag(ip, port);

    if (!c->is_client) {
        return;
    }

    for (auto &ctx : d->txBytes) {
        if (d->dataChannel == WEBSOCKET_OP_TEXT) {
            op = std::string("(T)");
            len = mg_ws_send(c, ctx.first.get(), ctx.second, WEBSOCKET_OP_TEXT);
        } else {
            op = std::string("(B)");
            len = mg_ws_send(c, ctx.first.get(), ctx.second, WEBSOCKET_OP_BINARY);
        }

        if (len > 0) {
            q->bytesTxSignal(ctx.first, ctx.second, to + op);
        } else {
            q->errorOccurredSignal(std::string("WS server send error"));
            break;
        }
    }

    d->txBytes.clear();
}

static void OnMgEvWsOpen(struct mg_connection *c, void *ev_data, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();

    const std::string locIp = d->mg_addr_to_ipv4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string remIp = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);

    wxtInfo() << "WebSocket client connected from " << locIp << ":" << locPort << " to " << remIp
              << ":" << remPort;
#if 0
    c->is_hexdumping = 1;
#endif
}

static void OnMessageRxTx(struct mg_connection *c, void *ev_data, WSClient *q, bool isRx)
{
    struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
    std::string op;
    if (wm->flags & WEBSOCKET_OP_TEXT) {
        op = std::string("(T)");
    } else if (wm->flags & WEBSOCKET_OP_BINARY) {
        op = std::string("(B)");
    } else {
        return;
    }

    std::string ip = q->GetD<WSClientPrivate>()->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string from = DoEncodeFlag(ip, port) + op;
    std::shared_ptr<char> bytes(new char[wm->data.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), wm->data.buf, wm->data.len);

    if (isRx) {
        q->bytesRxSignal(std::move(bytes), wm->data.len, from);
        wxtInfo() << "Received " << wm->data.len << " bytes from " << from;
    } else {
        q->bytesTxSignal(std::move(bytes), wm->data.len, from);
        wxtInfo() << "Sent " << wm->data.len << " bytes to " << from;
    }
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();
    const std::string ip = d->mg_addr_to_ipv4(&c->loc);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->loc.port);
    wxtInfo() << "WebSocket client closed from " << ip << ":" << port;
}

static void OnMgEvError(struct mg_connection *c, void *ev_data, WSClient *q)
{
    auto *d = q->GetD<WSClientPrivate>();
    const std::string ip = d->mg_addr_to_ipv4(&c->loc);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->loc.port);
    wxtError() << "Server error: " << ip << ":" << port;
}

static void WSClientHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto q = reinterpret_cast<WSClient *>(c->fn_data);
    if (ev == MG_EV_WS_OPEN) {
        OnMgEvWsOpen(c, ev_data, q);
    } else if (ev == MG_EV_WS_MSG) {
        OnMessageRxTx(c, ev_data, q, true);
    } else if (ev == MG_EV_WRITE) {
        OnMessageRxTx(c, ev_data, q, false);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    } else if (ev == MG_EV_ERROR) {
        OnMgEvError(c, ev_data, q);
    }
}
