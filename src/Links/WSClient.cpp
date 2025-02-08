﻿/***************************************************************************************************
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
    delete GetD<WSClientPrivate>();
}

void *WSClient::Entry()
{
    auto *d = GetD<WSClientPrivate>();
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
        d->DoTryToQueueError(_("Failed to create a WebSocket client."));
        mg_mgr_free(&mgr);
        return nullptr;
    }

    while (!TestDestroy()) {
        mg_mgr_poll(&mgr, 100);
    }

    mg_close_conn(c);
    mg_mgr_free(&mgr);
    wxtInfo() << "Web socket client thread exited...";
    return nullptr;
}
