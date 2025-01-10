﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio/io_service.hpp>
#include <asio/serial_port.hpp>

#include "Link.h"

struct SerialPortParameterKeys
{
    const std::string portName{"portName"};
    const std::string baudRate{"baudRate"};
    const std::string flowControl{"flowControl"};
    const std::string parity{"parity"};
    const std::string stopBits{"stopBits"};
    const std::string characterSize{"characterSize"};
};

class SerialPortPrivate;
class SerialPort : public Link
{
public:
    SerialPort();
    ~SerialPort();

    bool Open() override;
    void Close() override;
    void Write(const wxString &data, TextFormat format) override;
    void Load(const nlohmann::json &parameters) override;
    nlohmann::json Save() override;

private:
    SerialPortPrivate *d;
};
