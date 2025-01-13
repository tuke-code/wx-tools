﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "SocketServer.h"

class UDPServerPrivate;
class UDPServer : public SocketServer
{
public:
    UDPServer();
    ~UDPServer();

    bool Open() override;
    void Close() override;
    void Write(const wxString &data, TextFormat format) override;

private:
    UDPServerPrivate *d;
};