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

class SerialPort : public Communication
{
public:
    SerialPort();

    std::string GetPortName() const;
    void SetPortName(const std::string &portName);
    void SetBaudRate(int baudRate);
    void SetFlowControl(asio::serial_port::flow_control::type flowControl);
    void SetParity(asio::serial_port::parity::type parity);
    void SetStopBits(asio::serial_port::stop_bits::type stopBits);
    void SetCharacterSize(asio::serial_port::character_size dataBits);

    bool Open() override;
    void Close() override;
    void Write(const wxString &data, TextFormat format) override;

private:
    asio::serial_port *m_serialPort;
    asio::io_service m_ioService;
    std::string m_portName;
};
