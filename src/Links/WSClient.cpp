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
    mg_log_set(MG_LL_NONE);
    mgr.userdata = this;

    wxtInfo() << "Starting WS client on websocket:" << url.c_str();
    c = mg_ws_connect(&mgr, url.c_str(), WSClientHandler, &done, NULL);
    if (c == nullptr || done == true) {
        errorOccurredSignal(std::string("Failed to create a WebSocket client!"));
        return;
    }
#if 0
    const std::string locIp = d->mg_addr_to_ipv4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string remIp = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string loc = fmt::format("{0}:{1}", locIp, locPort);
    std::string rem = fmt::format("{0}:{1}", remIp, remPort);
    wxtInfo() << fmt::format("WebSocket client({0}) has been connected to {1}", loc, rem);
#endif

    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (1) {
        if (d->invokedInterrupted.load()) {
            mg_close_conn(c);
            break;
        }

        DoTryToSendBytesToClient(c, this);
        mg_mgr_poll(&mgr, 100);
    }
    mg_mgr_free(&mgr);

    d->isRunning.store(false);
}
