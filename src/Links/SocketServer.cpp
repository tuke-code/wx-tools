/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SocketServer.h"
#include "SocketServer_p.h"

SocketServer::SocketServer(SocketServerPrivate *dPtr)
    : SocketBase(reinterpret_cast<SocketBasePrivate *>(dPtr))
    , d(dPtr)
{}

SocketServer::~SocketServer() {}

void SocketServer::setCurrentClient(const std::string &ip, uint16_t port)
{
    d->selection = std::make_pair(ip, port);
}
