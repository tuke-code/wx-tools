/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SocketBase.h"

SocketBase::SocketBase() {}

SocketBase::~SocketBase() {}

void SocketBase::Load(const nlohmann::json &parameters)
{
    SocketBaseParameterKeys keys;
    m_clientAddress = parameters[keys.clientAddress].template get<std::string>();
    m_clientPort = parameters[keys.clientPort].template get<int>();
    m_serverAddress = parameters[keys.serverAddress].template get<std::string>();
    m_serverPort = parameters[keys.serverPort].template get<int>();
    m_isEnableAuthorization = parameters[keys.isAuthorization].template get<bool>();
    m_dataChannel = parameters[keys.dataChannel].template get<int>();
    m_userName = parameters[keys.userName].template get<std::string>();
    m_password = parameters[keys.password].template get<std::string>();
    Link::Load(parameters);
}

nlohmann::json SocketBase::Save()
{
    SocketBaseParameterKeys keys;
    nlohmann::json parameters;
    parameters[keys.clientAddress] = m_clientAddress.ToStdString();
    parameters[keys.clientPort] = m_clientPort;
    parameters[keys.serverAddress] = m_serverAddress.ToStdString();
    parameters[keys.serverPort] = m_serverPort;
    parameters[keys.isAuthorization] = m_isEnableAuthorization;
    parameters[keys.dataChannel] = m_dataChannel;
    parameters[keys.userName] = m_userName.ToStdString();
    parameters[keys.password] = m_password.ToStdString();
    return parameters;
}

wxString SocketBase::GetClientAddress() const
{
    return m_clientAddress;
}

uint16_t SocketBase::GetClientPort() const
{
    return m_clientPort;
}

wxString SocketBase::GetServerAddress() const
{
    return m_serverAddress;
}

uint16_t SocketBase::GetServerPort() const
{
    return m_serverPort;
}

bool SocketBase::GetIsEnableAuthorization() const
{
    return m_isEnableAuthorization;
}

int SocketBase::GetDataChannel() const
{
    return m_dataChannel;
}

wxString SocketBase::GetUserName() const
{
    return m_userName;
}

wxString SocketBase::GetPassword() const
{
    return m_password;
}
