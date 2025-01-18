/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <string>

#include <CSerialPort/SerialPort.h>

#include "Link_p.h"

class SerialPortPrivate : public LinkPrivate
{
public:
    std::string portName;
    int baudRate;
    itas109::FlowControl flowControl;
    itas109::Parity parity;
    itas109::StopBits stopBits;
    itas109::DataBits dataBits;
};
