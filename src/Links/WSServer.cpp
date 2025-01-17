﻿/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSServer.h"
#include "WSServer_p.h"

WSServer::WSServer()
    : SocketServer(d = new WSServerPrivate)
{}

WSServer::~WSServer()
{
    delete d;
    d = nullptr;
}

bool WSServer::Open()
{
    std::string ip = d->serverAddress.ToStdString();
    uint16_t port = d->serverPort;
    std::thread t(WSServerLoop, new WebSocketServer(ip, port));
    t.detach();
    return true;
}

void WSServer::Close() {}

void WSServer::Write(const wxString &data, TextFormat format) {}
