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

class SocketServerPrivate : public SocketBasePrivate
{
public:
    wxString targetAddressPort; // Such as "192.168.10.10:8080", or an empty string for all clients
    std::vector<std::pair<std::string, uint16_t>> clients;
    std::pair<std::string, uint16_t> selection;

    void DoRemoveClient(const std::string &address, uint16_t port)
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
