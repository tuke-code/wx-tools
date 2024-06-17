/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SerialPort.h"

#include <Common/Log.h>

SerialPort::SerialPort()
    : Communication()
    , m_serialPort(nullptr)
    , m_ioService(nullptr)
{}

void SerialPort::SetPortName(const std::string &portName)
{
    m_portName = portName;
}

void SerialPort::SetBaudRate(int baudRate)
{
    if (m_serialPort) {
        m_serialPort->set_option(asio::serial_port::baud_rate(baudRate));
    }
}

void SerialPort::SetFlowControl(asio::serial_port::flow_control::type flowControl)
{
    if (m_serialPort) {
        m_serialPort->set_option(asio::serial_port::flow_control(flowControl));
    }
}

void SerialPort::SetParity(asio::serial_port::parity::type parity)
{
    if (m_serialPort) {
        m_serialPort->set_option(asio::serial_port::parity(parity));
    }
}

void SerialPort::SetStopBits(asio::serial_port::stop_bits::type stopBits)
{
    if (m_serialPort) {
        m_serialPort->set_option(asio::serial_port::stop_bits(stopBits));
    }
}

void SerialPort::SetCharacterSize(asio::serial_port::character_size dataBits)
{
    if (m_serialPort) {
        m_serialPort->set_option(asio::serial_port::character_size(dataBits));
    }
}

bool SerialPort::OpenActually()
{
    if (m_serialPort) {
        return true;
    }

    m_ioService = new asio::io_service();
    m_serialPort = new asio::serial_port(*m_ioService);

    m_serialPort->set_option(asio::serial_port::baud_rate(115200));
    m_serialPort->set_option(asio::serial_port::flow_control(asio::serial_port::flow_control::none));
    m_serialPort->set_option(asio::serial_port::parity(asio::serial_port::parity::none));
    m_serialPort->set_option(asio::serial_port::stop_bits(asio::serial_port::stop_bits::one));
    m_serialPort->set_option(asio::serial_port::character_size(8));

    try {
        m_serialPort->open(m_portName);
    } catch (asio::system_error &e) {
        std::string errorString = e.what();
        errorString = "Open serial port failed, error message: " + errorString;
        LogInfo(errorString);
        return false;
    }

    return false;
}

void SerialPort::CloseActually()
{
    if (m_serialPort) {
        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = nullptr;

        m_ioService->stop();
        delete m_ioService;
        m_ioService = nullptr;
    }
}