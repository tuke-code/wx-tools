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
    size_t len = 0;
    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    std::string to = DoEncodeFlag(ip, port);

    d->txBytesLock.lock();
    for (auto &ctx : d->txBytes) {
        mg_send(c, ctx.first.get(), ctx.second);
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
    WXTDataItem item;
    item.len = c->recv.len;

    const std::string ip = d->mg_addr_to_ipv4(&c->rem);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string from = DoEncodeFlag(ip, port);
    item.flag = from;

    std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), c->recv.buf, c->recv.len);
    item.data = bytes;
    c->recv.len = 0;

    d->bytesRxLock.lock();
    d->bytesRx.push_back(item);
    d->bytesRxLock.unlock();
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    UDPClientPrivate *d = q->GetD<UDPClientPrivate>();
    d->errorMessagesLock.lock();
    d->errorMessage = _("UDP client disconnected");
    d->errorMessagesLock.unlock();
}

static void OnMgEvError(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    UDPClientPrivate *d = q->GetD<UDPClientPrivate>();
    d->errorMessagesLock.lock();
    d->errorMessage = reinterpret_cast<const char *>(ev_data);
    d->errorMessagesLock.unlock();
}

static void OnMgEvWrite(struct mg_connection *c, void *ev_data, UDPClient *q)
{
    UDPClientPrivate *d = q->GetD<UDPClientPrivate>();
    WXTDataItem item;
    item.len = *reinterpret_cast<const long *>(ev_data);
    if (item.len <= 0) {
        return;
    }

    item.data = std::shared_ptr<char>(new char[item.len], [](char *p) { delete[] p; });
    memcpy(item.data.get(), c->data, item.len);

    std::string ip = d->mg_addr_to_ipv4(&c->rem);
    uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    item.flag = DoEncodeFlag(ip, port);

    d->bytesTxLock.lock();
    d->bytesTx.push_back(item);
    d->bytesTxLock.unlock();
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
    } else if (ev == MG_EV_WRITE) {
        OnMgEvWrite(c, ev_data, q);
    }
}
