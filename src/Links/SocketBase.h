﻿/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>

#include "Link.h"

struct SocketBaseParameterKeys
{
    const std::string clientAddress{"clientAddress"};
    const std::string clientPort{"clientPort"};
    const std::string serverAddress{"serverAddress"};
    const std::string serverPort{"serverPort"};
    const std::string isAuthorization{"isEnableAuthorization"};
    const std::string dataChannel{"dataChannel"};
    const std::string userName{"userName"};
    const std::string password{"password"};
};

class SocketBasePrivate;
class SocketBase : public Link
{
public:
    SocketBase(SocketBasePrivate *d);
    ~SocketBase();

    void Load(const nlohmann::json &parameters) override;
    nlohmann::json Save() override;

    wxString GetClientAddress() const;
    uint16_t GetClientPort() const;
    wxString GetServerAddress() const;
    uint16_t GetServerPort() const;
    bool GetIsEnableAuthorization() const;
    int GetDataChannel() const;
    wxString GetUserName() const;
    wxString GetPassword() const;

    static std::string DoEncodeFlag(const std::string &ip, uint16_t port);
    static std::pair<std::string, uint16_t> DoDecodeFlag(const std::string &flag);

private:
    SocketBasePrivate *d;
};
