/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "SocketBase_p.h"

class SocketClientPrivate : public SocketBasePrivate
{
public:
    void OnMgEvOpen(struct mg_connection *c)
    {
        const std::string locIp = DoMgAddressToIpV4(&c->loc);
        const uint16_t locPort = DoReverseByteOrder<uint16_t>(c->loc.port);

        wxtInfo() << fmt::format("Client socket opened({0}:{1}).", locIp, locPort);
        DoQueueLinkOpened();
    }

    void OnMgEvRead(struct mg_connection *c, void *ev_data)
    {
        if (c->recv.len <= 0) {
            return;
        }

        wxtDataItem item;
        item.len = c->recv.len;

        const std::string ip = DoMgAddressToIpV4(&c->rem);
        const uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
        const std::string from = DoEncodeFlag(ip, port);
        item.flag = from;

        std::shared_ptr<char> bytes(new char[c->recv.len], [](char *p) { delete[] p; });
        memcpy(bytes.get(), c->recv.buf, c->recv.len);
        item.data = bytes;
        DoQueueTxBytes(bytes, c->recv.len, from);
        c->recv.len = 0;
    }

    void OnMgEvClose(struct mg_connection *c, void *ev_data)
    {
        if (evtHandler) {
            wxtInfo() << fmt::format("Client socket closed({0}:{1}).",
                                     clientAddress.ToStdString(),
                                     clientPort);
            DoQueueError(GetStrClientClosed());
            DoQueueLinkClosed();
        }
    }

    void OnMgEvError(struct mg_connection *c, void *ev_data)
    {
        wxtInfo() << fmt::format("Client socket error({0}:{1}):{2}",
                                 clientAddress.ToStdString(),
                                 clientPort,
                                 reinterpret_cast<char *>(ev_data));
    }

    void DoPoll(struct mg_connection *c, int ev, void *ev_data) override
    {
        SocketBasePrivate::DoPoll(c, ev, ev_data);

        if (ev == MG_EV_OPEN) {
            OnMgEvOpen(c);
        } else if (ev == MG_EV_READ) {
            OnMgEvRead(c, ev_data);
        } else if (ev == MG_EV_CLOSE) {
            OnMgEvClose(c, ev_data);
        } else if (ev == MG_EV_ERROR) {
            OnMgEvError(c, ev_data);
        }
    }
};
