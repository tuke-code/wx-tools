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
    std::string clientAddress;
    m_clientAddress = parameters.at(std::string(keys.clientAddress.mb_str())).get_to(clientAddress);
    m_clientPort = parameters.at(std::string(keys.clientPort.mb_str())).get<uint16_t>();
    m_serverAddress = parameters.at(std::string(keys.serverAddress.mb_str())).get<std::string>();
    m_serverPort = parameters.at(std::string(keys.serverPort.mb_str())).get<uint16_t>();
    m_isEnableAuthorization = parameters.at(std::string(keys.isAuthorization.mb_str())).get<bool>();
    m_dataChannel = parameters.at(std::string(keys.dataChannel.mb_str())).get<int>();
    m_userName = parameters.at(std::string(keys.userName.mb_str())).get<std::string>();
    m_password = parameters.at(std::string(keys.password.mb_str())).get<std::string>();

    Communication::Load(parameters);
}

nlohmann::json SocketBase::Save()
{
    SocketBaseParameterKeys keys;
    nlohmann::json parameters;
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