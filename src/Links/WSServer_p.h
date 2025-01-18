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
};

void OnAccept(struct mg_connection *c, WSServer *server)
{
    std::string ip = server->GetPrivate<WSServerPrivate>()->mg_addr_to_ipv4(&c->rem);
    std::string from = ip + std::string(":") + std::to_string(c->rem.port);
    server->newClientSignal(ip, c->rem.port);

    if (c->next && c->next->rem.port) {
        OnAccept(c->next, server);
    }
}

static void WSServerLoop(struct mg_connection *c, int ev, void *ev_data)
{
    WSServer *q = reinterpret_cast<WSServer *>(c->mgr->userdata);
    WSServerPrivate *d = q->GetPrivate<WSServerPrivate>();

    if (ev == MG_EV_OPEN) {
        // c->is_hexdumping = 1;
    } else if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_match(hm->uri, mg_str("/websocket"), NULL)) {
            // Upgrade to websocket. From now on, a connection is a full-duplex
            // Websocket connection, which will receive MG_EV_WS_MSG events.
            mg_ws_upgrade(c, hm, NULL);
        }
    } else if (ev == MG_EV_ACCEPT) {
        if (q && c && c->fd) {
            OnAccept(c, q);
        }
    } else if (ev == MG_EV_WS_MSG) {
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        std::string op;
        if (wm->flags & WEBSOCKET_OP_TEXT) {
            op = std::string("(T)");
        } else if (wm->flags & WEBSOCKET_OP_BINARY) {
            op = std::string("(B)");
        }

        std::string ip = d->mg_addr_to_ipv4(&c->rem);
        uint16_t port = c->rem.port;
        std::string from = DoEncodeFlag(ip, port) + op;
        std::shared_ptr<char> bytes(new char[wm->data.len], [](char *p) { delete[] p; });
        memcpy(bytes.get(), wm->data.buf, wm->data.len);
        q->bytesRxSignal(std::move(bytes), from);
    } else if (ev == MG_EV_ERROR) {
        q->errorOccurredSignal(std::string("WS server error"));
    }
}
