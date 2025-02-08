﻿/***************************************************************************************************
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
#include "SocketServer_p.h"
#include "WSServer.h"

class WSServerPrivate : public SocketServerPrivate
{
public:
};

static void DoSendBytesToClient(struct mg_connection *c, void *ev_data, WSServer *q)
{
    auto *d = q->GetD<WSServerPrivate>();
    std::string op;
    size_t len = 0;
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string to = DoEncodeFlag(ip, port);

    if (c->rem.port == 0) {
        return;
    }

    for (auto &ctx : d->txBytes) {
        if (d->dataChannel == WEBSOCKET_OP_TEXT) {
            op = std::string("(T)");
            len = mg_ws_send(c, ctx.first.get(), ctx.second, WEBSOCKET_OP_TEXT);
        } else if (d->dataChannel == WEBSOCKET_OP_TEXT) {
            op = std::string("(B)");
            len = mg_ws_send(c, ctx.first.get(), ctx.second, WEBSOCKET_OP_BINARY);
        } else {
            wxtWarning() << "Unknown data channel: " << d->dataChannel;
            break;
        }

        if (len > 0) {
            d->DoTryToQueueTxBytes(ctx.first, ctx.second, to + op);
        } else {
            d->DoTryToDeleteClient(ip, port);
            break;
        }
    }
}

static void OnMgEvOpen(struct mg_connection *c, void *ev_data, WSServer *q)
{
    auto *d = q->GetD<WSServerPrivate>();
    const std::string ip = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    if (port == 0) {
        // The server is opened...
        return;
    }

    d->DoTryToNewClient(ip, port);
    wxtInfo() << "Server open: " << ip << ":" << port;
}

static void OnMgEvHttpMsg(struct mg_connection *c, void *ev_data, WSServer *q)
{
    WXUNUSED(q);
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_match(hm->uri, mg_str("/websocket"), NULL)) {
        // Upgrade to websocket. From now on, a connection is a full-duplex
        // Websocket connection, which will receive MG_EV_WS_MSG events.
        mg_ws_upgrade(c, hm, NULL);
    }
}

static void OnAccept(struct mg_connection *c, WSServer *q)
{
    if (c == nullptr) {
        return;
    }

    if (!c->is_client) {
        return;
    }

    if (q == nullptr) {
        return;
    }

    std::string ip = q->GetD<WSServerPrivate>()->mg_addr_to_ipv4(&c->rem);
    const uint8_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string from = ip + std::string(":") + std::to_string(port);
    auto *d = q->GetD<WSServerPrivate>();
    d->DoTryToNewClient(ip, port);
    wxtInfo() << "Client connected: " << from;
}

static void OnMgEvMsg(struct mg_connection *c, void *ev_data, WSServer *q)
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

    auto *d = q->GetD<WSServerPrivate>();
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string from = DoEncodeFlag(ip, port) + op;
    wxtInfo() << wm->flags << wm->data.len;
    std::shared_ptr<char> bytes(new char[wm->data.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), wm->data.buf, wm->data.len);

    d->DoTryToQueueRxBytes(bytes, wm->data.len, from);
    wxtInfo() << "Received " << wm->data.len << " bytes from " << from;
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, WSServer *q)
{
    WSServerPrivate *d = q->GetD<WSServerPrivate>();
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    if (c->is_client) {
        d->DoTryToDeleteClient(ip, port);
    } else {
        d->DoTryToCloseLink();
        wxtInfo() << "Server close: " << ip << ":" << port;
    }
}

static void OnMgEvError(struct mg_connection *c, void *ev_data, WSServer *q)
{
    WSServerPrivate *d = q->GetD<WSServerPrivate>();
    std::string msg = fmt::format("Error occurred: {0}", ev_data);
    if (c->is_client) {
        std::string ip = d->mg_addr_to_ipv4(&c->rem);
        uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
        d->DoTryToDeleteClient(ip, port);
    } else {
        d->DoTryToQueueErrorOccurred(msg);
    }
}

static void OnMgEvPoll(struct mg_connection *c, void *ev_data, WSServer *q)
{
    auto *d = q->GetD<WSServerPrivate>();
    if (d->txBytes.empty()) {
        return;
    }

    if (d->selection.first.empty() && d->selection.second == 0) {
        // Send to all clients
        for (struct mg_connection *conns = c; conns != nullptr; conns = conns->next) {
            DoSendBytesToClient(c, ev_data, q);
        }
    } else {
        for (struct mg_connection *conns = c; conns != nullptr; conns = conns->next) {
            const std::string ip = d->mg_addr_to_ipv4(&conns->rem);
            const uint8_t port = DoReverseByteOrder<uint16_t>(conns->rem.port);
            if (ip == d->selection.first && port == d->selection.second) {
                DoSendBytesToClient(c, ev_data, q);
                break;
            }
        }
    }

    d->txBytes.clear();
}

static void WSServerHandler(struct mg_connection *c, int ev, void *ev_data)
{
    WSServer *q = reinterpret_cast<WSServer *>(c->mgr->userdata);
    if (!q) {
        wxtWarning() << "You must set the server object before calling this function";
        return;
    }

    if (ev == MG_EV_OPEN) {
        OnMgEvOpen(c, ev_data, q);
    } else if (ev == MG_EV_HTTP_MSG) {
        OnMgEvHttpMsg(c, ev_data, q);
    } else if (ev == MG_EV_ACCEPT) {
        OnAccept(c, q);
    } else if (ev == MG_EV_WS_MSG) {
        OnMgEvMsg(c, ev_data, q);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    } else if (ev == MG_EV_ERROR) {
        //OnMgEvError(c, ev_data, q);
    } else if (ev == MG_EV_POLL) {
        OnMgEvPoll(c, ev_data, q);
    }
}
