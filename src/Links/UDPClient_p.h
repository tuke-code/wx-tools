/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <fmt/format.h>

#include "SocketClient_p.h"
#include "UDPClient.h"

class UDPClientPrivate : public SocketClientPrivate
{
public:
};

static void OnMgEvPoll(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    auto *d = q->GetD<UDPClientPrivate>();
    d->txBytesLock.lock();
    for (auto &ctx : d->txBytes) {
        if (mg_send(c, ctx.first.get(), ctx.second)) {
            std::string ip = d->mg_addr_to_ipv4(&c->rem);
            uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
            std::string to = DoEncodeFlag(ip, port);
            d->DoTryToQueueTxBytes(ctx.first, ctx.second, to);
        } else {
            d->DoTryToQueueError(_("UDP client sends bytes failed."));
            break;
        }
    }

    d->txBytes.clear();
    d->txBytesLock.unlock();
}

static void OnMgEvOpen(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    auto *d = q->GetD<UDPClientPrivate>();
    const std::string remIp = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string locIp = d->mg_addr_to_ipv4(&c->loc);
    const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);
    const std::string from = DoEncodeFlag(remIp, remPort);
    const std::string to = DoEncodeFlag(locIp, locPort);

    wxtInfo() << fmt::format("UDP client connected from {0} to {1}", from, to);
}

static void OnMgEvRead(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    if (c->recv.len <= 0) {
        return;
    }

    UDPClientPrivate *d = q->GetD<UDPClientPrivate>();
    wxtDataItem item;
    item.len = c->recv.len;

    const std::string ip = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string from = DoEncodeFlag(ip, port);
    item.flag = from;

    std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), c->recv.buf, c->recv.len);
    item.data = bytes;
    c->recv.len = 0;

    if (d && d->evtHandler) {
        auto *evt = new wxThreadEvent(wxEVT_THREAD, wxtBytesTx);
        evt->SetPayload<wxtDataItem>(item);
        d->evtHandler->QueueEvent(evt);
    }
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    UDPClientPrivate *d = q->GetD<UDPClientPrivate>();
    wxString msg = _("UDP client disconnected");
    if (d && d->evtHandler) {
        auto *evt = new wxThreadEvent(wxEVT_THREAD, wxtErrorOccurred);
        evt->SetString(msg);
        d->evtHandler->QueueEvent(evt);
    }
}

static void OnMgEvError(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    UDPClientPrivate *d = q->GetD<UDPClientPrivate>();
    std::string msg = reinterpret_cast<const char *>(ev_data);
    if (d && d->evtHandler) {
        auto *evt = new wxThreadEvent(wxEVT_THREAD, wxtErrorOccurred);
        evt->SetString(msg);
        d->evtHandler->QueueEvent(evt);
    }
}

static void UDPClientHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto *q = reinterpret_cast<UDPClient *>(c->mgr->userdata);
    if (ev == MG_EV_OPEN) {
        OnMgEvOpen(c, ev_data, q);
    } else if (ev == MG_EV_READ) {
        OnMgEvRead(c, ev_data, q);
    } else if (ev == MG_EV_POLL) {
        OnMgEvPoll(c, ev_data, q);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    } else if (ev == MG_EV_ERROR) {
        OnMgEvError(c, ev_data, q);
    }
}
