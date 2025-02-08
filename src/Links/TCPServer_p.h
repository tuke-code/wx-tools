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

#include "SocketServer_p.h"
#include "TCPServer.h"

class TCPServerPrivate : public SocketServerPrivate
{
public:
};

static void OnMgEvOpen(struct mg_connection *c, void *ev_data, TCPServer *q)
{
    auto *d = q->GetD<TCPServerPrivate>();
    d->DoQueueLinkOpened();
}

static void OnMgEvRead(struct mg_connection *c, void *ev_data, TCPServer *q)
{
    if (c->recv.len <= 0) {
        return;
    }

    std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
    memcpy(bytes.get(), c->recv.buf, c->recv.len);

    auto *d = q->GetD<TCPServerPrivate>();
    const std::string ip = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
    const std::string from = DoEncodeFlag(ip, port);

    d->DoTryToNewClient(ip, port);
    d->DoQueueRxBytes(bytes, c->recv.len, from);
    c->recv.len = 0;
}

static void OnMgEvAccept(struct mg_connection *c, void *ev_data, TCPServer *q)
{
    auto *d = q->GetD<TCPServerPrivate>();
    c->is_client = true;
    const std::string remIp = d->DoMgAddressToIpV4(&c->rem);
    const uint16_t remPort = DoReverseByteOrder<uint16_t>(c->rem.port);
    d->DoTryToNewClient(remIp, remPort);
}

static void OnMgEvPoll(struct mg_connection *c, void *ev_data, TCPServer *q)
{
    auto *d = q->GetD<TCPServerPrivate>();
    if (d->selection.first.empty() && d->selection.second == 0) {
        for (auto con = c; con != nullptr; con = con->next) {
            if (con->is_client) {
                d->DoTryToSendBytes(c, ev_data);
            }
        }
    } else {
        for (auto con = c; con != nullptr; con = con->next) {
            std::string ip = d->DoMgAddressToIpV4(&con->rem);
            uint16_t port = DoReverseByteOrder<uint16_t>(con->rem.port);
            if (con->is_client && d->selection.first == ip && d->selection.second == port) {
                d->DoTryToSendBytes(c, ev_data);
                break;
            }
        }
    }

    d->DoClrearTxBytes();
}

static void OnMgEvClose(struct mg_connection *c, void *ev_data, TCPServer *q)
{
    auto *d = q->GetD<TCPServerPrivate>();
    if (c->is_client) {
        std::string ip = d->DoMgAddressToIpV4(&c->rem);
        uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
        d->DoTryToDeleteClient(ip, port);
    } else {
        d->DoQueueError(d->GetStrServerClosed());
        d->DoQueueLinkClosed();
    }
}

static void TCPServerHandler(struct mg_connection *c, int ev, void *ev_data)
{
    auto *q = reinterpret_cast<TCPServer *>(c->mgr->userdata);
    wxASSERT_MSG(q, "q is nullptr");

    if (ev == MG_EV_OPEN) {
        OnMgEvOpen(c, ev_data, q);
    } else if (ev == MG_EV_READ) {
        OnMgEvRead(c, ev_data, q);
    } else if (ev == MG_EV_ACCEPT) {
        OnMgEvAccept(c, ev_data, q);
    } else if (ev == MG_EV_POLL) {
        OnMgEvPoll(c, ev_data, q);
    } else if (ev == MG_EV_CLOSE) {
        OnMgEvClose(c, ev_data, q);
    }
}
