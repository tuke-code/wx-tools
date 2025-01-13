﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPClient.h"
#include "TCPClient_p.h"

TCPClient::TCPClient()
    : d(new TCPClientPrivate)
    , SocketClient(d)
{}

TCPClient::~TCPClient()
{
    delete d;
    d = nullptr;
}

bool TCPClient::Open()
{
    return false;
}

void TCPClient::Close() {}

void TCPClient::Write(const wxString &data, TextFormat format) {}