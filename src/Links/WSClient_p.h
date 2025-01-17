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

#include "SocketServer_p.h"

class WebSocketClient;
class WSClientPrivate : public SocketServerPrivate
{
public:
    WebSocketClient *client{nullptr};
};

class WebSocketClient
{
public:
    WebSocketClient()
        : invokedInterrupted(false)
        , running(false)
    {}

public:
    sigslot::signal<std::shared_ptr<char> /*data*/, int /*len*/, std::string /*from*/> bytesRx;
    sigslot::signal<std::shared_ptr<char> /*data*/, int /*len*/, std::string /*to  */> bytesTx;
    sigslot::signal<std::string> errorOccurred;

    std::atomic_bool invokedInterrupted;
    std::atomic_bool running;
    std::vector<std::pair<std::shared_ptr<char> /*data*/, int /*len*/>> txBytes;
};

static void handler(struct mg_connection *c, int ev, void *ev_data)
{
    if (ev == MG_EV_OPEN) {
        //c->is_hexdumping = 1;
    } else if (ev == MG_EV_ERROR) {
        // On error, log error message
        //MG_ERROR(("%p %s", c->fd, (char *) ev_data));
    } else if (ev == MG_EV_WS_OPEN) {
        // When websocket handshake is successful, send message
        mg_ws_send(c, "hello", 5, WEBSOCKET_OP_TEXT);
    } else if (ev == MG_EV_WS_MSG) {
        // When we get echo response, print it
        struct mg_ws_message *wm = (struct mg_ws_message *) ev_data;
        //printf("GOT ECHO REPLY: [%.*s]\n", (int) wm->data.len, wm->data.buf);
    }

    if (ev == MG_EV_ERROR || ev == MG_EV_CLOSE || ev == MG_EV_WS_MSG) {
        *(bool *) c->fn_data = true; // Signal that we're done
    }
}

static void WSClientLoop(WebSocketClient *client, const std::string &ip, uint16_t port)
{
    client->running.store(true);
    const std::string url = "ws://" + ip + ":" + std::to_string(port);
    struct mg_mgr mgr;
    bool done = false;
    struct mg_connection *c;
    mgr.userdata = client;
    mg_mgr_init(&mgr);
    c = mg_ws_connect(&mgr, url.c_str(), handler, &done, NULL);
    while (c && done == false) {
        if (client->invokedInterrupted.load()) {
            break;
        }

        for (auto &tx : client->txBytes) {
            mg_ws_send(mgr.conns, tx.first.get(), tx.second, WEBSOCKET_OP_TEXT);
        }

        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    client->running.store(false);
}
