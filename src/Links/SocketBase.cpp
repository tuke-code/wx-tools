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

SocketBase::SocketBase(SocketBasePrivate *dPtr)
    : d(dPtr)
{}

SocketBase::~SocketBase() {}

void SocketBase::Load(const nlohmann::json &parameters)
{
    SocketBaseParameterKeys keys;
    d->clientAddress = parameters[keys.clientAddress].template get<std::string>();
    d->clientPort = parameters[keys.clientPort].template get<int>();
    d->serverAddress = parameters[keys.serverAddress].template get<std::string>();
    d->serverPort = parameters[keys.serverPort].template get<int>();
    d->isEnableAuthorization = parameters[keys.isAuthorization].template get<bool>();
    d->dataChannel = parameters[keys.dataChannel].template get<int>();
    d->userName = parameters[keys.userName].template get<std::string>();
    d->password = parameters[keys.password].template get<std::string>();
}

nlohmann::json SocketBase::Save()
{
    SocketBaseParameterKeys keys;
    nlohmann::json parameters;
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

wxString SocketBase::GetClientAddress() const
{
    return d->clientAddress;
}

uint16_t SocketBase::GetClientPort() const
{
    return d->clientPort;
}

wxString SocketBase::GetServerAddress() const
{
    return d->serverAddress;
}

uint16_t SocketBase::GetServerPort() const
{
    return d->serverPort;
}

bool SocketBase::GetIsEnableAuthorization() const
{
    return d->isEnableAuthorization;
}

int SocketBase::GetDataChannel() const
{
    return d->dataChannel;
}

wxString SocketBase::GetUserName() const
{
    return d->userName;
}

wxString SocketBase::GetPassword() const
{
    return d->password;
}

std::string SocketBase::DoEncodeFlag(const std::string &ip, uint16_t port)
{
    return ip + ":" + std::to_string(port);
}

std::pair<std::string, uint16_t> SocketBase::DoDecodeFlag(const std::string &flag)
{
    std::pair<std::string, uint16_t> result{"", 0};
    size_t pos = flag.find(':');
    if (pos != std::string::npos) {
        result.first = flag.substr(0, pos);
        result.second = std::stoi(flag.substr(pos + 1));
    }
    return result;
}
