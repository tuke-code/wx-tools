/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SocketBase.h"
#include "SocketBase_p.h"

SocketBase::SocketBase(SocketBasePrivate *d)
    : Link(d)
{}

SocketBase::~SocketBase() {}

void SocketBase::Load(const wxtJson &parameters)
{
    SocketBasePrivate *d = WXT_D(SocketBasePrivate);
    SocketBaseParameterKeys keys;
    d->clientAddress = parameters[keys.clientAddress].get<std::string>();
    d->clientPort = parameters[keys.clientPort].get<int>();
    d->serverAddress = parameters[keys.serverAddress].get<std::string>();
    d->serverPort = parameters[keys.serverPort].get<int>();
    d->isEnableAuthorization = parameters[keys.isAuthorization].get<bool>();
    d->dataChannel = parameters[keys.dataChannel].get<int>();
    d->userName = parameters[keys.userName].get<std::string>();
    d->password = parameters[keys.password].get<std::string>();
}

wxtJson SocketBase::Save()
{
    SocketBasePrivate *d = WXT_D(SocketBasePrivate);
    SocketBaseParameterKeys keys;
    wxtJson parameters;
    parameters[keys.clientAddress] = d->clientAddress.ToStdString();
    parameters[keys.clientPort] = d->clientPort;
    parameters[keys.serverAddress] = d->serverAddress.ToStdString();
    parameters[keys.serverPort] = d->serverPort;
    parameters[keys.isAuthorization] = d->isEnableAuthorization;
    parameters[keys.dataChannel] = d->dataChannel;
    parameters[keys.userName] = d->userName.ToStdString();
    parameters[keys.password] = d->password.ToStdString();
    return parameters;
}
