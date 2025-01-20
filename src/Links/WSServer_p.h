/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "Common/wxTools.h"
#include "SocketServer_p.h"
#include "WSServer.h"

class WSServerPrivate : public SocketServerPrivate
{
public:
    WSServerPrivate()
        : invokeClearClients(false)
    {}

    std::atomic_bool invokeClearClients;
};

static void DoClearAllClients(struct mg_mgr *mgr, WSServer *q)
{
    auto *d = q->GetD<WSServerPrivate>();
    auto *c = mgr->conns;
    for (struct mg_connection *connection = c; connection != nullptr; connection = c->next) {
        if (connection->is_client) {
            std::string ip = d->mg_addr_to_ipv4(&connection->rem);
            uint16_t port = connection->rem.port;
            d->DoRemoveClient(ip, port);
            q->deleteClientSignal(ip, port);
            mg_close_conn(connection);
        }
    }
}

static void DoSendBytesToClient(struct mg_connection *c, WSServer *q)
{
    auto *d = q->GetD<WSServerPrivate>();
    std::string op;
    size_t len = 0;
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = c->rem.port;
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
            d->DoRemoveClient(ip, port);
            q->deleteClientSignal(ip, port);
            q->errorOccurredSignal(std::string("WS server send error"));
            break;
        }
    }
}

static void DoSendBytesToAllClients(mg_mgr *mgr, WSServer *q)
{
    auto *d = q->GetD<WSServerPrivate>();
    if (d->selection.first.empty() && d->selection.second == 0) { // Send to all clients
        auto *c = mgr->conns;
        for (struct mg_connection *connection = c; connection != nullptr; connection = c->next) {
            DoSendBytesToClient(connection, q);
        }
    } else {
        auto *c = mgr->conns;
        for (struct mg_connection *connection = c; connection != 0; connection = c->next) {
            const std::string ip = d->mg_addr_to_ipv4(&connection->rem);
            const uint8_t port = connection->rem.port;
            if (ip == d->selection.first && port == d->selection.second) {
                DoSendBytesToClient(connection, q);
            }
        }
    }

    d->txBytes.clear();
}

static void OnMgEvOpen(struct mg_connection *c, void *ev_data, WSServer *q)
{
    WXUNUSED(c);
    WXUNUSED(ev_data);
    WXUNUSED(q);
#if 0
    c->is_hexdumping = 1;
#endif
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

static void OnAccept(struct mg_connection *c, WSServer *server)
{
    if (!(c && c->is_client)) {
        return;
    }

    std::string ip = server->GetD<WSServerPrivate>()->mg_addr_to_ipv4(&c->rem);
    std::string from = ip + std::string(":") + std::to_string(c->rem.port);
    server->newClientSignal(ip, c->rem.port);
    wxtInfo() << "New client from " << from;

#if 0
    if (c->next && c->next->rem.port) {
        OnAccept(c->next, server);
    }
#endif
}

static void OnMessageRxTx(struct mg_connection *c, WSServer *q, void *ev_data, bool isRx)
{
    struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
    std::string op;
    if (wm->flags & WEBSOCKET_OP_TEXT) {
        op = std::string("(T)");
    } else if (wm->flags & WEBSOCKET_OP_BINARY) {
        op = std::string("(B)");
    }

    std::string ip = q->GetD<WSServerPrivate>()->mg_addr_to_ipv4(&c->rem);
    uint16_t port = c->rem.port;
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

void OnMgEvClose(struct mg_connection *c, void *ev_data, WSServer *q)
{
#if 0
    WSServerPrivate *d = q->GetD<WSServerPrivate>();
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = c->rem.port;
    q->deleteClientSignal(ip, port);
    d->DoRemoveClient(ip, port);
#endif
}

static void OnMgEvError(struct mg_connection *c, void *ev_data, WSServer *q)
{
    WXUNUSED(c);
    WXUNUSED(ev_data);
    q->errorOccurredSignal(std::string("WS server error"));
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
        OnMessageRxTx(c, q, ev_data, true);
    } else if (ev == MG_EV_WRITE) {
        OnMessageRxTx(c, q, ev_data, false);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    } else if (ev == MG_EV_ERROR) {
        OnMgEvError(c, ev_data, q);
    }
}
