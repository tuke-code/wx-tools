/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSClient.h"
#include "WSClient_p.h"

WSClient::WSClient()
    : d(new WSClientPrivate)
    , SocketClient(d)
{}

WSClient::~WSClient()
{
    delete d;
    d = nullptr;
}

bool WSClient::Open()
{
    return false;
}

void WSClient::Close() {}

void WSClient::Write(const wxString &data, TextFormat format) {}
