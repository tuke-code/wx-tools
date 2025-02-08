/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <fmt/format.h>

#include "Common/wxTools.h"
#include "SocketServer_p.h"
#include "UDPServer.h"

class UDPServerPrivate : public SocketServerPrivate
{
public:
};

static void OnErrorOccurred(const wxString &msg, UDPServerPrivate *d)
{
    if (d && d->evtHandler) {
        auto *evt = new wxThreadEvent(wxEVT_THREAD, wxtErrorOccurred);
        evt->SetString(msg);
        d->evtHandler->QueueEvent(evt);
    }
}

static void OnMgEvPoll(struct mg_connection *c, void *ev_data, UDPServer *q)
{
    auto *d = q->GetD<UDPServerPrivate>();
    if (d->selection.first.empty() && d->selection.second == 0) {
        for (auto &client : d->clients) {
            if (d->DoIpV4ToMgAddress(client.first, &c->rem)) {
                (&c->rem)->port = DoReverseByteOrder(client.second);
                d->DoTryToSendBytes(c, ev_data);
            }
        }
    } else {
        if (d->DoIpV4ToMgAddress(d->selection.first, &c->rem)) {
            (&c->rem)->port = DoReverseByteOrder(d->selection.second);
            d->DoTryToSendBytes(c, ev_data);
        }
    }

    d->DoClrearTxBytes();
}

static void OnMgEvOpen(struct mg_connection *c, void *ev_data, UDPServer *q)
{
    auto *d = q->GetD<UDPServerPrivate>();
    const std::string remIp = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string locIp = d->DoMgAddressToIpV4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string from = DoEncodeFlag(remIp, remPort);
    const std::string to = DoEncodeFlag(locIp, locPort);

    wxtInfo() << fmt::format("UDP client connected from {0} to {1}", from, to);
}

static void OnMgEvRead(struct mg_connection *c, void *ev_data, UDPServer *q)
{
    if (c->recv.len <= 0) {
        return;
    }

    std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), c->recv.buf, c->recv.len);

    auto *d = q->GetD<UDPServerPrivate>();
    const std::string ip = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string from = DoEncodeFlag(ip, port);

    d->DoTryToNewClient(ip, port);
    d->DoQueueRxBytes(bytes, c->recv.len, from);
    c->recv.len = 0;
}

static void UDPServerHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto *q = reinterpret_cast<UDPServer *>(c->mgr->userdata);
    if (ev == MG_EV_OPEN) {
        OnMgEvOpen(c, ev_data, q);
    } else if (ev == MG_EV_READ) {
        OnMgEvRead(c, ev_data, q);
    } else if (ev == MG_EV_POLL) {
        OnMgEvPoll(c, ev_data, q);
    }
}
