/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SerialPort.h"
#include "SerialPort_p.h"

SerialPort::SerialPort()
    : Link()
    , d(new SerialPortPrivate())
{}

SerialPort::~SerialPort()
{

}

void ReadData(SerialPortPrivate *d, SerialPort *serialPort)
{
    
}

bool SerialPort::Open()
{
    return false;
}

void SerialPort::Close()
{

}

void SerialPort::Write(const wxString &data, TextFormat format)
{

}

void SerialPort::Load(const wxToolsJson &parameters)
{
#if 0
    // clang-format off
    SerialPortParameterKeys keys;
    d->portName = parameters[keys.portName].template get<std::string>();
    d->baudRate = parameters[keys.baudRate].template get<int>();
    d->flowControl = static_cast<asio::serial_port::flow_control::type>(parameters[keys.flowControl].template get<int>());
    d->parity = static_cast<asio::serial_port::parity::type>(parameters[keys.parity].template get<int>());
    d->stopBits = static_cast<asio::serial_port::stop_bits::type>(parameters[keys.stopBits].template get<int>());
    d->dataBits = static_cast<asio::serial_port::character_size>(parameters[keys.characterSize].template get<int>());
    // clang-format on
#endif
}

wxToolsJson SerialPort::Save()
{
#if 0
    wxToolsJson parameters;
    SerialPortParameterKeys keys;
    parameters[keys.portName] = d->portName;
    parameters[keys.baudRate] = d->baudRate;
    parameters[keys.flowControl] = static_cast<int>(d->flowControl);
    parameters[keys.parity] = static_cast<int>(d->parity);
    parameters[keys.stopBits] = static_cast<int>(d->stopBits);
    parameters[keys.characterSize] = static_cast<int>(d->dataBits.value());
    return parameters;
#endif
    return wxToolsJson();
}
