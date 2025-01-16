/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <string>

#include <wx/wx.h>

class SocketBasePrivate
{
public:
    wxString clientAddress;
    uint16_t clientPort;
    wxString serverAddress;
    uint16_t serverPort;

    // The members for web socket
    bool isEnableAuthorization;
    int dataChannel;
    wxString userName;
    wxString password;

    std::string DoEncodeFlag(const std::string &ip, uint16_t port)
    {
        return ip + ":" + std::to_string(port);
    }

    std::pair<std::string, uint16_t> DoDecodeFlag(const std::string &flag)
    {
        std::pair<std::string, uint16_t> result{"", 0};
        size_t pos = flag.find(':');
        if (pos != std::string::npos) {
            result.first = flag.substr(0, pos);
            result.second = std::stoi(flag.substr(pos + 1));
        }
        return result;
    }
};