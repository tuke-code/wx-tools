/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPClient.h"
#include "TCPClient_p.h"

#include <fmt/format.h>
#include <mongoose.h>

TCPClient::TCPClient()
    : SocketClient(new TCPClientPrivate)
{}

TCPClient::~TCPClient()
{
    delete GetD<TCPClientPrivate>();
}

void *TCPClient::Entry()
{
    auto d = GetD<TCPClientPrivate>();
    std::string url = fmt::format("tcp://{0}:{1}", d->serverAddress.ToStdString(), d->serverPort);
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_log_set(MG_LL_NONE);

    mgr.userdata = this;
    auto *c = mg_connect(&mgr, url.c_str(), TCPClientHandler, nullptr);
    if (c == nullptr) {
        d->DoTryToQueueError(_("Failed to connect to tcp server."));
        mg_mgr_free(&mgr);
        return nullptr;
    }

#if 1
    const std::string remIp = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string locIp = d->mg_addr_to_ipv4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string from = DoEncodeFlag(remIp, remPort);
    const std::string to = DoEncodeFlag(locIp, locPort);

    wxtInfo() << fmt::format("TCP client connected from {0} to {1}", from, to);
#endif

    while (!TestDestroy()) {
        mg_mgr_poll(&mgr, 100);
    }

    mg_mgr_free(&mgr);
    wxtInfo() << "TCP client thread exited...";
    return nullptr;
}
