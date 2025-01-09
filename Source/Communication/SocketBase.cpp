﻿/***************************************************************************************************
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

void SocketBase::Load(const wxJSONValue &parameters)
{
    SocketBaseParameterKeys keys;
    m_clientAddress = parameters.Get(keys.clientAddress, wxJSONValue("127.0.0.0")).AsString();
    m_clientPort = parameters.Get(keys.clientPort, wxJSONValue(54321)).AsUInt();
    m_serverAddress = parameters.Get(keys.serverAddress, wxJSONValue("127.0.0.0")).AsString();
    m_serverPort = parameters.Get(keys.serverPort, wxJSONValue(54321)).AsUInt();
    m_isEnableAuthorization = parameters.Get(keys.isAuthorization, wxJSONValue(false)).AsBool();
    m_dataChannel = parameters.Get(keys.dataChannel, wxJSONValue(0)).AsUInt();
    m_userName = parameters.Get(keys.userName, wxJSONValue("")).AsString();
    m_password = parameters.Get(keys.password, wxJSONValue("")).AsString();

    Communication::Load(parameters);
}

wxJSONValue SocketBase::Save()
{
    SocketBaseParameterKeys keys;
    wxJSONValue parameters;
    parameters[std::string(keys.clientAddress.mb_str())] = m_clientAddress.ToStdString();
    parameters[std::string(keys.clientPort.mb_str())] = m_clientPort;
    parameters[std::string(keys.serverAddress.mb_str())] = m_serverAddress.ToStdString();
    parameters[std::string(keys.serverPort.mb_str())] = m_serverPort;
    parameters[std::string(keys.isAuthorization.mb_str())] = m_isEnableAuthorization;
    parameters[std::string(keys.dataChannel.mb_str())] = m_dataChannel;
    parameters[std::string(keys.userName.mb_str())] = m_userName.ToStdString();
    parameters[std::string(keys.password.mb_str())] = m_password.ToStdString();
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