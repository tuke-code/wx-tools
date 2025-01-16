/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>

#include "Common/wxTools.h"
#include "SocketServer_p.h"

using asio::ip::udp;

class UDPServerPrivate : public SocketServerPrivate
{
public:
    wxToolsSignal<wxString, TextFormat> invokeWriteSignal;
    wxToolsSignal<> invokeCloseSignal;

    asio::io_context context;
    udp::socket *socket{nullptr};

    void removeClient(const std::string &address, uint16_t port)
    {
        auto it = std::find_if(clients.begin(),
                               clients.end(),
                               [&](const std::pair<std::string, uint16_t> &client) {
                                   return client.first == address && client.second == port;
                               });

        if (it != clients.end()) {
            clients.erase(it);
        }
    }
};
