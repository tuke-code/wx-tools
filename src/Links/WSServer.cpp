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
    delete GetD<WSServerPrivate *>();
}

#if 0
void WSServer::Poll()
{
    auto *d = GetD<WSServerPrivate>();
    std::string url = std::string("ws://") + d->serverAddress.ToStdString();
    url += std::string(":");
    url += std::to_string(d->serverPort);
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_NONE);
    mgr.userdata = this;

    wxtInfo() << Save().dump().c_str();
    auto *c = mg_http_listen(&mgr, url.c_str(), WSServerHandler, nullptr);
    if (c == nullptr) {
        mg_mgr_free(&mgr);
        d->DoQueueError(d->GetStrFailedToCreateServer());
        return;
    }

    c->is_client = false;
    while (!TestDestroy()) {
        mg_mgr_poll(&mgr, 100);
    }

    mg_mgr_free(&mgr);
    wxtInfo() << "Web socket server thread is exited!";
}
#endif
