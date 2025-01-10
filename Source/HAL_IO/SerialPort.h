/***************************************************************************************************
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

#include "Communication.h"

struct SerialPortParameterKeys
{
    const wxString portName{"portName"};
    const wxString baudRate{"baudRate"};
    const wxString flowControl{"flowControl"};
    const wxString parity{"parity"};
    const wxString stopBits{"stopBits"};
    const wxString characterSize{"characterSize"};
};

class SerialPortPrivate;
class SerialPort : public Communication
{
public:
    SerialPort();
    ~SerialPort();

    bool Open() override;
    void Close() override;
    void Write(const wxString &data, TextFormat format) override;
    void Load(const wxJSONValue &parameters) override;
    wxJSONValue Save() override;

private:
    SerialPortPrivate *d;
};
