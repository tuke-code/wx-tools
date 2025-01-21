/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPServer.h"
#include "TCPServer_p.h"

TCPServer::TCPServer()
    : SocketServer(new TCPServerPrivate)
{}

TCPServer::~TCPServer()
{
    delete GetD<TCPServerPrivate>();
}

void TCPServer::Loop()
{
    auto d = GetD<TCPServerPrivate>();
    std::string url = fmt::format("tcp://{0}:{1}", d->serverAddress.ToStdString(), d->serverPort);
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_NONE);

    mgr.userdata = this;
    struct mg_connection *c = mg_listen(&mgr, url.c_str(), TCPServerHandler, nullptr);
    if (c == nullptr) {
        std::string log(fmt::format("Failed to connect to the server: {0}", url));
        wxtInfo() << log;
        errorOccurredSignal(log);
        return;
    }

    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (!d->invokedInterrupted.load()) {
        mg_mgr_poll(&mgr, 100);
    }

    mg_mgr_free(&mgr);
    d->isRunning.store(false);
    wxtInfo() << "UDP client thread exited...";
}
