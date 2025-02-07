/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPClient.h"
#include "UDPClient_p.h"

#include <fmt/format.h>
#include <mongoose.h>

UDPClient::UDPClient()
    : SocketClient(new UDPClientPrivate)
{}

UDPClient::~UDPClient()
{
    
}

void *UDPClient::Entry()
{
    UDPClientPrivate *d = GetD<UDPClientPrivate>();
    std::string url = fmt::format("udp://{0}:{1}", d->serverAddress.ToStdString(), d->serverPort);
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_NONE);

    mgr.userdata = this;
    struct mg_connection *c = mg_connect(&mgr, url.c_str(), UDPClientHandler, nullptr);
    if (c == nullptr) {
        d->DoTryToQueueErrorOccurred(_("Failed to connect to the server."));
        mg_mgr_free(&mgr);
        return nullptr;
    }

    while (!TestDestroy()) {
        mg_mgr_poll(&mgr, 100);
    }

    mg_mgr_free(&mgr);
    wxtInfo() << "UDP client thread exited...";
    return nullptr;
}
