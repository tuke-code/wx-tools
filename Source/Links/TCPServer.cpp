/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPServer.h"
#include "TCPServer_p.h"

TCPServer::TCPServer()
    : d(new TCPServerPrivate)
    , SocketServer(d)
{}

TCPServer::~TCPServer()
{
    delete d;
    d = nullptr;
}

bool TCPServer::Open()
{
    return false;
}

void TCPServer::Close() {}

void TCPServer::Write(const wxString &data, TextFormat format) {}
