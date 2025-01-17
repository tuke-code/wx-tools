/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <atomic>

#include <mongoose.h>
#include <sigslot/signal.hpp>

#include "Common/wxTools.h"
#include "SocketServer_p.h"

class WebSocketServer;
class WSServerPrivate : public SocketServerPrivate
{
public:
    WebSocketServer *server{nullptr};
};

class WebSocketServer
{
public:
    WebSocketServer()
        : invokedInterrupted(false)
        , running(false)
    {}

public:
    sigslot::signal<std::shared_ptr<int *> /*data*/, int /*len*/, std::string /*from*/> bytesRx;
    sigslot::signal<std::shared_ptr<int *> /*data*/, int /*len*/, std::string /*to  */> bytesTx;
    sigslot::signal<std::string> errorOccurred;

    std::atomic_bool invokedInterrupted;
    std::atomic_bool running;
    std::vector<std::pair<std::shared_ptr<int *> /*data*/, int /*len*/>> txBytes;
};

static void handler(struct mg_connection *c, int ev, void *ev_data)
{
    if (ev == MG_EV_OPEN) {
        // c->is_hexdumping = 1;
    } else if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_match(hm->uri, mg_str("/websocket"), NULL)) {
            // Upgrade to websocket. From now on, a connection is a full-duplex
            // Websocket connection, which will receive MG_EV_WS_MSG events.
            mg_ws_upgrade(c, hm, NULL);
        } else if (mg_match(hm->uri, mg_str("/rest"), NULL)) {
            // Serve REST response
            mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
        } else {
            // Serve static files
            struct mg_http_serve_opts opts = {.root_dir = "."};
            //mg_http_serve_dir(c, ev_data, &opts);
        }
    } else if (ev == MG_EV_WS_MSG) {
        // Got websocket frame. Received data is wm->data. Echo it back!
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        if (wm->flags & WEBSOCKET_OP_TEXT) {
            wxToolsInfo() << "Text: " << wm->data.buf;
        } else if (wm->flags & WEBSOCKET_OP_BINARY) {
            wxToolsInfo() << "Binary: " << wm->data.buf;
        }
        //mg_ws_send(c, wm->data.buf, wm->data.len, WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_ERROR) {
        wxToolsInfo() << "Error: " << "WS server error";
    }
}

static void WSServerLoop(WebSocketServer *server, const std::string &ip, uint16_t port)
{
    server->running.store(true);
    const std::string url = "ws://" + ip + ":" + std::to_string(port);
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, url.c_str(), handler, server);
    while (1) {
        if (server->invokedInterrupted.load()) {
            break;
        }

        for (auto &tx : server->txBytes) {
            mg_ws_send(mgr.conns, tx.first.get(), tx.second, WEBSOCKET_OP_TEXT);
        }

        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    server->running.store(false);
}
