/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSServer.h"
#include "WSServer_p.h"

WSServer::WSServer()
    : SocketServer(new WSServerPrivate)
{}

WSServer::~WSServer()
{
    delete WXT_D(WSServerPrivate);
}

void WSServer::DoClearClients()
{
    d->invokedInterrupted.store(true);
    while (!d->invokedInterrupted.load()) {
        break;
    }
}

void WSServer::Loop()
{
    auto *d = WXT_D(WSServerPrivate);
    std::string url = std::string("ws://") + d->serverAddress.ToStdString();
    url += std::string(":");
    url += std::to_string(d->serverPort);
    struct mg_mgr mgr;

    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_NONE);
    mgr.userdata = this;
    mg_connection *c = mg_http_listen(&mgr, url.c_str(), WSServerHandler, nullptr);
    if (c == nullptr) {
        errorOccurredSignal(std::string("Failed to create a WebSocket server!"));
        return;
    }

    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (1) {
        if (d->invokedInterrupted.load()) {
            mg_close_conn(c);
            break;
        }

        DoClearClients();
        SendBytesToAllClients(&mgr, this);
        mg_mgr_poll(&mgr, 100);
    }
    mg_mgr_free(&mgr);

    // Remove all clients
    auto tmp = d->clients;
    for (auto &client : tmp) {
        d->DoRemoveClient(client.first, client.second);
        deleteClientSignal(client.first, client.second);
    }

    d->isRunning.store(false);
}
