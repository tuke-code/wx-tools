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

#include <mongoose.h>

UDPClient::UDPClient()
    : SocketClient(new UDPClientPrivate)
{}

UDPClient::~UDPClient()
{
    delete WXT_D(UDPClientPrivate);
}

static void UDPClientHandler(struct mg_connection *c, int ev, void *ev_data)
{
    MG_DEBUG(("%p got event: %d %p", c, ev, ev_data));
    if (ev == MG_EV_OPEN) {
        // Nothing to do yet...
    } else if (ev == MG_EV_RESOLVE) {
        // c->rem gets populated with multicast address. Store it in c->data
        memcpy(c->data, &c->rem, sizeof(c->rem));
    } else if (ev == MG_EV_READ) {
        struct mg_http_message hm;
        if (mg_http_parse((const char *) c->recv.buf, c->recv.len, &hm) > 0) {
            size_t i, max = sizeof(hm.headers) / sizeof(hm.headers[0]);
            // Iterate over request headers
            for (i = 0; i < max && hm.headers[i].name.len > 0; i++) {
                struct mg_str k = hm.headers[i].name, v = hm.headers[i].value;
                if ((mg_strcasecmp(k, mg_str("SERVER")) == 0)
                    || (mg_strcasecmp(k, mg_str("LOCATION")) == 0)) {
                    printf("\t%.*s -> %.*s\n", (int) k.len, k.buf, (int) v.len, v.buf);
                }
            }
            printf("\n");
        }
        // Each response to the SSDP socket will change c->rem.
        // We can now do mg_printf(c, "haha"); to respond back to the remote side.
        // But in our case, we should restore the multicast address in order
        // to have next search to go to the multicast address
        memcpy(&c->rem, c->data, sizeof(c->rem));
        // Discard the content of this response as we expect each SSDP response
        // to generate at most one MG_EV_READ event.
        c->recv.len = 0UL;
    }
}

void UDPClient::Loop()
{
    auto d = WXT_D(UDPClientPrivate);
    std::string url = std::string("udp://") + d->serverAddress.ToStdString();
    url += ":" + std::to_string(d->serverPort);

    struct mg_mgr mgr;
    struct mg_connection *c;
    mg_mgr_init(&mgr);
    c = mg_connect(&mgr, url.c_str(), UDPClientHandler, nullptr);
    if (c == nullptr) {
        errorOccurredSignal("Failed to connect to the server.");
        return;
    }

    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (1) {
        if (d->invokedInterrupted.load()) {
            break;
        }

        for (auto ctx : d->txBytes) {
            if (mg_send(c, ctx.first.get(), ctx.second)) {
            } else {
                errorOccurredSignal("Send data failed.");
                d->invokedInterrupted.store(true);
                break;
            }
        }
        d->txBytes.clear();

        mg_mgr_poll(&mgr, 50);
    }
    mg_mgr_free(&mgr);
    d->isRunning.store(false);
}
