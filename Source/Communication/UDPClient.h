﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>

#include "SocketClient.h"

class UDPClient : public SocketClient
{
public:
    UDPClient();
    ~UDPClient();

    bool Open() override;
    void Close() override;
    void Write(const wxString &data, TextFormat format) override;

private:
    asio::io_context m_ioContext;
    asio::ip::udp::socket *m_socket;
    asio::ip::udp::endpoint m_endpoint;
};