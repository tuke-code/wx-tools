/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "Link.h"
#include "SocketBase_p.h"

class SocketServerPrivate : public SocketBasePrivate
{
public:
    wxString targetAddressPort; // Such as "192.168.10.10:8080", or an empty string for all clients
    std::vector<std::pair<std::string, uint16_t>> clients;
    std::pair<std::string, uint16_t> selection;

    void DoTryToDeleteClient(const std::string &address, uint16_t port)
    {
        if (clients.empty()) {
            return;
        }

        auto it = std::find_if(clients.begin(),
                               clients.end(),
                               [&](const std::pair<std::string, uint16_t> &client) {
                                   return client.first == address && client.second == port;
                               });

        if (it != clients.end()) {
            clients.erase(it);
        }

        // If the client is the current selection, clear the selection
        if (address == selection.first && port == selection.second) {
            selection = std::make_pair("", 0);
        }

        if (evtHandler) {
            wxThreadEvent *evt = new wxThreadEvent(wxEVT_THREAD, wxtDeleteClient);
            evt->SetString(address);
            evt->SetInt(port);
            evtHandler->QueueEvent(evt);
        }
    }

    void DoTryToNewClient(const std::string &address, uint16_t port)
    {
        auto client = std::make_pair(address, port);
        if (std::find(clients.begin(), clients.end(), client) == clients.end()) {
            clients.push_back(client);

            if (evtHandler) {
                wxThreadEvent *evt = new wxThreadEvent(wxEVT_THREAD, wxtNewClient);
                evt->SetString(address);
                evt->SetInt(port);
                evtHandler->QueueEvent(evt);
            }
        }
    }

    void DoTryToSendBytes(struct mg_connection *c, void *ev_data)
    {
        wxUnusedVar(ev_data);

        std::string ip = DoMgAddressToIpV4(&c->rem);
        uint16_t port = DoReverseByteOrder<uint16_t>(c->rem.port);
        std::string to = DoEncodeFlag(ip, port);

        txBytesLock.lock();
        for (auto &ctx : txBytes) {
            if (mg_send(c, ctx.first.get(), ctx.second)) {
                DoQueueTxBytes(ctx.first, ctx.second, to);
            } else {
                DoTryToDeleteClient(ip, port);
            }
        }
        txBytesLock.unlock();
    }
};
