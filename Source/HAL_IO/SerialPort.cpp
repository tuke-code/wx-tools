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
    : Communication()
    , d(new SerialPortPrivate())
{}

SerialPort::~SerialPort()
{
    delete d;
}

void ReadData(SerialPortPrivate *d, SerialPort *serialPort)
{
    if (!d->serialPort || !serialPort) {
        return;
    }

    char buffer[1024] = {0};
    size_t receivedBytes = 0;
    while (1) {
        try {
            receivedBytes = d->serialPort->read_some(asio::buffer(buffer, sizeof(buffer)));
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            wxString msg = wxString::Format("Read data failed, error message: %s", errorString);
            wxToolsInfo() << msg;
            break;
        }

        if (receivedBytes > 0) {
            std::string data(buffer, receivedBytes);
            asio::const_buffer buffer(data.data(), data.size());
            std::string portName = d->portName;
            serialPort->bytesReadSignal(buffer, d->portName);
        }
    }

    delete d->serialPort;
}

bool SerialPort::Open()
{
    if (d->serialPort) {
        d->serialPort->close();
    }

    d->serialPort = new asio::serial_port(d->ioService);
    try {
        d->serialPort->open(d->portName);
    } catch (asio::system_error &e) {
        d->ioService.stop();

        std::string errorString = e.what();
        errorString = "Open serial port failed, error message: " + errorString;
        wxToolsInfo() << errorString;
        return false;
    }

    std::thread t(ReadData, d, this);
    t.detach();

    return true;
}

void SerialPort::Close()
{
    if (d->serialPort) {
        d->serialPort->close();
    }
}

void SerialPort::Write(const wxString &data, TextFormat format)
{
    const std::string msg = data.ToStdString();
    if (d->serialPort && d->serialPort->is_open() && !msg.empty()) {
        auto buffer = asio::buffer(msg.data(), msg.size());
        size_t ret = d->serialPort->write_some(buffer);
        if (ret > 0) {
            bytesWrittenSignal(buffer, d->portName);
        } else {
            wxToolsWarning() << "Write data failed.";
        }
    }
}

void SerialPort::Load(const wxJSONValue &parameters)
{
    // clang-format off
    SerialPortParameterKeys keys;
    d->portName = parameters.Get(keys.portName, wxJSONValue("")).AsString();
    d->baudRate = parameters.Get(keys.baudRate, wxJSONValue(9600)).AsInt();
    d->flowControl = static_cast<asio::serial_port::flow_control::type>(parameters.Get(keys.flowControl, wxJSONValue(asio::serial_port::flow_control::type::none)).AsInt());
    d->parity = static_cast<asio::serial_port::parity::type>(parameters.Get(keys.parity, wxJSONValue(asio::serial_port::parity::type::none)).AsInt());
    d->stopBits = static_cast<asio::serial_port::stop_bits::type>(parameters.Get(keys.stopBits, wxJSONValue(asio::serial_port::stop_bits::type::one)).AsInt());
    d->dataBits = static_cast<asio::serial_port::character_size>(parameters.Get(keys.characterSize, wxJSONValue(8)).AsInt());
    // clang-format on
}

wxJSONValue SerialPort::Save()
{
    wxJSONValue parameters;
    SerialPortParameterKeys keys;
    parameters[keys.portName] = d->portName;
    parameters[keys.baudRate] = d->baudRate;
    parameters[keys.flowControl] = static_cast<int>(d->flowControl);
    parameters[keys.parity] = static_cast<int>(d->parity);
    parameters[keys.stopBits] = static_cast<int>(d->stopBits);
    parameters[keys.characterSize] = static_cast<int>(d->dataBits.value());
    return parameters;
}