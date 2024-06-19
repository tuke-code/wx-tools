/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SerialPortInfo.h"

SerialPortInfo::SerialPortInfo() {}

std::vector<int> SerialPortInfo::standardBaudRates()
{
    return {110, 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200};
}

std::vector<SerialPortInfo> SerialPortInfo::availablePorts()
{
    return {};
}
