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
{}

std::string SerialPort::GetPortName() const
{
    return m_portName;
}

void SerialPort::SetPortName(const std::string &portName)
{
    m_portName = portName;
}

void SerialPort::SetBaudRate(int baudRate)
{
    if (m_serialPort) {
        try {
            m_serialPort->set_option(asio::serial_port::baud_rate(baudRate));
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            errorString = "Set baud rate failed, error message: " + errorString;
            LogInfo(errorString);
        }
    }
}

void SerialPort::SetFlowControl(asio::serial_port::flow_control::type flowControl)
{
    if (m_serialPort) {
        try {
            m_serialPort->set_option(asio::serial_port::flow_control(flowControl));
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            errorString = "Set flow control failed, error message: " + errorString;
            LogInfo(errorString);
        }
    }
}

void SerialPort::SetParity(asio::serial_port::parity::type parity)
{
    if (m_serialPort) {
        try {
            m_serialPort->set_option(asio::serial_port::parity(parity));
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            errorString = "Set parity failed, error message: " + errorString;
            LogInfo(errorString);
        }
    }
}

void SerialPort::SetStopBits(asio::serial_port::stop_bits::type stopBits)
{
    if (m_serialPort) {
        try {
            m_serialPort->set_option(asio::serial_port::stop_bits(stopBits));
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            errorString = "Set stop bits failed, error message: " + errorString;
            LogInfo(errorString);
        }
    }
}

void SerialPort::SetCharacterSize(asio::serial_port::character_size dataBits)
{
    if (m_serialPort) {
        try {
            m_serialPort->set_option(asio::serial_port::character_size(dataBits));
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            errorString = "Set character size failed, error message: " + errorString;
            LogInfo(errorString);
        }
    }
}

void ReadData(asio::serial_port **serialPort, SerialPort *serialPortInstance)
{
    while (1) {
        if ((*serialPort)) {
            char buffer[1024] = {0};
            try {
                size_t ret = (*serialPort)->read_some(asio::buffer(buffer, sizeof(buffer)));

                if (ret > 0) {
                    std::string data(buffer, ret);
                    asio::const_buffer buffer(data.data(), data.size());
                    std::string portName = serialPortInstance->GetPortName();
                    serialPortInstance->GetBytesReadSignal()(buffer, portName);
                }
            } catch (asio::system_error &e) {
                break;
            }
        }
    }
#if 0
    delete (*serialPort);
#endif
}

bool SerialPort::Open()
{
    if (m_serialPort) {
        m_serialPort->close();
    }

    m_serialPort = new asio::serial_port(m_ioService);
    try {
        m_serialPort->open(m_portName);
    } catch (asio::system_error &e) {
        m_ioService.stop();

        std::string errorString = e.what();
        errorString = "Open serial port failed, error message: " + errorString;
        LogInfo(errorString);
        return false;
    }

    std::thread t(ReadData, &m_serialPort, this);
    t.detach();

    return true;
}

void SerialPort::Close()
{
    if (m_serialPort) {
        m_serialPort->close();
    }
}

void SerialPort::Write(const wxString &data, TextFormat format)
{
    LogInfo("Write data");
    const std::string msg = data.ToStdString();
    if (m_serialPort && m_serialPort->is_open() && !msg.empty()) {
        auto buffer = asio::buffer(msg.data(), msg.size());
        size_t ret = m_serialPort->write_some(buffer);
        if (ret > 0) {
            m_bytesWrittenSignal(buffer, m_portName);
        } else {
            LogWarning("Write data failed.");
        }
    }
}
