/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SocketServerUi.h"

SocketServerUi::SocketServerUi(wxWindow *parent)
    : SocketBaseUi(parent)
{}

SocketServerUi::~SocketServerUi() {}

wxString SocketServerUi::DoMakeFlag(const wxString &ip, uint16_t port)
{
    // Such as: "127.0.0.1:55443"
    return ip + ":" + std::to_string(port);
}
