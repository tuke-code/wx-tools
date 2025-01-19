/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSClient.h"
#include "WSClient_p.h"

WSClient::WSClient()
    : SocketClient(new WSClientPrivate)
{}

WSClient::~WSClient()
{
    delete WXT_D(WSClientPrivate);
}

void WSClient::Loop()
{
    auto *d = WXT_D(WSClientPrivate);
    std::string ip = d->serverAddress.ToStdString();
    uint16_t port = d->serverPort;
    const std::string url = "ws://" + ip + ":" + std::to_string(port);

    struct mg_mgr mgr;
    bool done = false;
    struct mg_connection *c;
    mgr.userdata = this;
    mg_mgr_init(&mgr);
    mgr.userdata = this;
    c = mg_ws_connect(&mgr, url.c_str(), WSClientHandler, &done, NULL);
    if (c == nullptr || done == true) {
        errorOccurredSignal(std::string("Failed to create a WebSocket client!"));
        return;
    }

    mg_log_set(MG_LL_NONE);

    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (1) {
        if (d->invokedInterrupted.load()) {
            break;
        }

        for (auto &tx : d->txBytes) {
            mg_ws_send(mgr.conns, tx.first.get(), tx.second, WEBSOCKET_OP_TEXT);
        }

        d->txBytes.clear();
        mg_mgr_poll(&mgr, 100);
    }
    mg_mgr_free(&mgr);

    for (auto &client : d->clients) {
    }

    d->isRunning.store(false);
}
