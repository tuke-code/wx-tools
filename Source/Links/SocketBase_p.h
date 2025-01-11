/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/wx.h>

class SocketBasePrivate
{
public:
    wxString clientAddress;
    uint16_t clientPort;
    wxString serverAddress;
    uint16_t serverPort;

    // The members for web socket
    bool m_isEnableAuthorization;
    int m_dataChannel;
    wxString m_userName;
    wxString m_password;
};