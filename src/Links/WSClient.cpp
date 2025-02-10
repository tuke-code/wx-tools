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
    delete GetD<WSClientPrivate *>();
}

#if 0
void WSClient::Poll()
{
    auto *d = GetD<WSClientPrivate>();
    std::string ip = d->serverAddress.ToStdString();
    uint16_t port = d->serverPort;
    const std::string url = fmt::format("ws://{0}:{1}", ip, port);

    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_NONE);
    mgr.userdata = this;
    auto c = mg_ws_connect(&mgr, url.c_str(), WSClientHandler, nullptr, nullptr);
    if (c == nullptr) {
        d->DoQueueError(d->GetStrClientClosed());
        mg_mgr_free(&mgr);
        return;
    }

    while (!TestDestroy()) {
        mg_mgr_poll(&mgr, 100);
    }

    mg_mgr_free(&mgr);
    wxtInfo() << "Web socket client thread exited...";
}
#endif
