/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>

#include "SocketClient.h"

class UDPClientPrivate;
class UDPClient : public SocketClient
{
public:
    UDPClient();
    ~UDPClient();

    bool Open() override;
    void Close() override;
    void Write(const wxString &data, TextFormat format) override;

private:
    UDPClientPrivate *d;
};