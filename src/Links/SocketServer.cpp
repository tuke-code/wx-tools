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

SocketServer::SocketServer(SocketServerPrivate *d)
    : SocketBase(reinterpret_cast<SocketBasePrivate *>(d))
{}

SocketServer::~SocketServer()
{

}

void SocketServer::SetCurrentClient(const std::string &ip, uint16_t port)
{
    SocketServerPrivate *d = WXT_D(SocketServerPrivate);
    d->selection = std::make_pair(ip, port);
}

void SocketServer::DoClearClients()
{
    // Clear the clients list
    SocketServerPrivate *d = WXT_D(SocketServerPrivate);
    for (auto client : d->clients) {
        deleteClientSignal(client.first, client.second);
    }

    d->clients.clear();
}
