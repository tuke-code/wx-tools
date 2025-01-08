/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>

#include "Communication.h"

struct SocketBaseParameterKeys
{
    const wxString clientAddress{"clientAddress"};
    const wxString clientPort{"clientPort"};
    const wxString serverAddress{"serverAddress"};
    const wxString serverPort{"serverPort"};
    const wxString isAuthorization{"isEnableAuthorization"};
    const wxString dataChannel{"dataChannel"};
    const wxString userName{"userName"};
    const wxString password{"password"};
};

class SocketBase : public Communication
{
public:
    SocketBase();
    ~SocketBase();

    void Load(const wxJSONValue &parameters) override;
    wxJSONValue Save() override;

protected:
    wxString m_clientAddress;
    uint16_t m_clientPort;
    wxString m_serverAddress;
    uint16_t m_serverPort;

    // The members for web socket
    bool m_isEnableAuthorization;
    int m_dataChannel;
    wxString m_userName;
    wxString m_password;
};