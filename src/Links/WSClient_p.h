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
#include "SocketServer_p.h"

class WSClientPrivate : public SocketServerPrivate
{
public:
};

static void WSClientHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto q = reinterpret_cast<WSClient *>(c->fn_data);
    auto d = q->GetD<WSClientPrivate>();

    if (ev == MG_EV_OPEN) {
        //c->is_hexdumping = 1;
    } else if (ev == MG_EV_ERROR) {
        // On error, log error message
        //MG_ERROR(("%p %s", c->fd, (char *) ev_data));
    } else if (ev == MG_EV_WS_OPEN) {
        // When websocket handshake is successful, send message
        mg_ws_send(c, "hello", 5, WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_WS_MSG) {
        //WebSocketClient *client = (WebSocketClient *) c->mgr->userdata;
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        std::shared_ptr<char> data(new char[wm->data.len], [](char *p) { delete[] p; });
        memcpy(data.get(), wm->data.buf, wm->data.len);

        const std::string ip = d->mg_addr_to_ipv4(&c->rem);
        const uint16_t port = c->rem.port;
        const std::string from = DoEncodeFlag(ip, port);
        q->bytesRxSignal(std::move(data), wm->data.len, from);
    } else if (ev == MG_EV_WRITE) {
    } else if (ev == MG_EV_CLOSE) {
        // When connection is closed, log message
        //MG_INFO(("%p closed", c->fd));
    }

    if (ev == MG_EV_ERROR || ev == MG_EV_CLOSE) {
        q->errorOccurredSignal(std::string("WebSocket client disconnected!"));
    }
}
