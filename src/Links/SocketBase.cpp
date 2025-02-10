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
    auto *d = GetD<SocketBasePrivate *>();
    SocketBaseParameterKeys keys;
    if (parameters.contains(keys.clientAddress)) {
        d->clientAddress = parameters[keys.clientAddress].get<std::string>();
    } else {
        d->clientAddress = "127.0.0.1";
    }

    if (parameters.contains(keys.clientPort)) {
        d->clientPort = parameters[keys.clientPort].get<int>();
    } else {
        d->clientPort = 51234;
    }

    if (parameters.contains(keys.serverAddress)) {
        d->serverAddress = parameters[keys.serverAddress].get<std::string>();
    } else {
        d->serverAddress = "127.0.0.1";
    }

    if (parameters.contains(keys.serverPort)) {
        d->serverPort = parameters[keys.serverPort].get<int>();
    } else {
        d->serverPort = 51234;
    }

    if (parameters.contains(keys.isAuthorization)) {
        d->isEnableAuthorization = parameters[keys.isAuthorization].get<bool>();
    } else {
        d->isEnableAuthorization = false;
    }

    if (parameters.contains(keys.dataChannel)) {
        d->dataChannel = parameters[keys.dataChannel].get<int>();
    } else {
        d->dataChannel = WEBSOCKET_OP_TEXT;
    }

    if (parameters.contains(keys.userName)) {
        d->userName = parameters[keys.userName].get<std::string>();
    } else {
        d->userName = "";
    }

    if (parameters.contains(keys.password)) {
        d->password = parameters[keys.password].get<std::string>();
    } else {
        d->password = "";
    }
}

wxtJson SocketBase::Save()
{
    auto *d = GetD<SocketBasePrivate *>();
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
