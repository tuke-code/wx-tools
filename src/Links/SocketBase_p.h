/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <mongoose.h>
#include <wx/wx.h>

#include "Link_p.h"

class SocketBasePrivate : public LinkPrivate
{
public:
    SocketBasePrivate()
        : LinkPrivate()
        , isEnableAuthorization(false)
        , dataChannel(0)
    {}

    wxString clientAddress;
    uint16_t clientPort;
    wxString serverAddress;
    uint16_t serverPort;

    // The members for web socket
    bool isEnableAuthorization;
    int dataChannel;
    wxString userName;
    wxString password;

    std::string mg_addr_to_ipv4(const struct mg_addr *addr)
    {
        if (addr == nullptr) {
            return std::string("0.0.0.0");
        }

        char ipv4[4] = {0};
        memcpy(ipv4, addr->ip, 4);
        std::string ip;
        for (int i = 0; i < 4; i++) {
            ip += std::to_string(static_cast<uint8_t>(ipv4[i]));
            if (i < 3) {
                ip += ".";
            }
        }

        return ip;
    }
};
