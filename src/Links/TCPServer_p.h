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
    std::string GetProtocolName() const override { return std::string("tcp"); }
    mg_connection *DoConnection(struct mg_mgr *mgr, const char *url, mg_event_handler_t fn) override
    {
        return mg_listen(mgr, url, fn, nullptr);
    }
    bool GetIsClient() const override { return false; }

public:
    void OnMgEvPoll(struct mg_connection *c, void *ev_data)
    {
        if (selection.first.empty() && selection.second == 0) {
            for (auto con = c; con != nullptr; con = con->next) {
                if (con->is_client) {
                    DoTryToSendBytes(c);
                }
            }
        } else {
            for (auto con = c; con != nullptr; con = con->next) {
                std::string ip = DoMgAddressToIpV4(&con->rem);
                uint16_t port = DoReverseByteOrder<uint16_t>(con->rem.port);
                if (con->is_client && selection.first == ip && selection.second == port) {
                    DoTryToSendBytes(c);
                    break;
                }
            }
        }

        DoClrearTxBytes();
    }

    void DoPoll(struct mg_connection *c, int ev, void *ev_data) override
    {
        SocketServerPrivate::DoPoll(c, ev, ev_data);
        if (ev == MG_EV_POLL) {
            OnMgEvPoll(c, ev_data);
        }
    }
};
