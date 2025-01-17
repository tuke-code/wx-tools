/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio/io_service.hpp>
#include <asio/serial_port.hpp>

#include "Link_p.h"

class SerialPortPrivate : public LinkPrivate
{
public:
    asio::serial_port *serialPort;
    asio::io_service ioService;
    std::string portName;
    int baudRate;
    asio::serial_port::flow_control::type flowControl;
    asio::serial_port::parity::type parity;
    asio::serial_port::stop_bits::type stopBits;
    asio::serial_port::character_size dataBits;
};
