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
    : Link(d = new SerialPortPrivate())
{}

SerialPort::~SerialPort()
{
    delete d;
}

void SerialPort::Loop(LinkPrivate *d)
{
    SerialPortPrivate *dPtr = reinterpret_cast<SerialPortPrivate *>(d);

    d->invokedInterrupted.store(false);
    auto *serialPortIml = new itas109::CSerialPort();
    serialPortIml->init(dPtr->portName.c_str(),
                        dPtr->baudRate,
                        dPtr->parity,
                        dPtr->dataBits,
                        dPtr->stopBits,
                        dPtr->flowControl);

    if (serialPortIml->open()) {
        d->isRunning.store(true);
        while (1) {
            if (d->invokedInterrupted.load()) {
                break;
            }

            // Read data....
            char data[10240] = {0};
            int len = serialPortIml->readAllData(&data);
            if (len == -1) {
                errorOccurredSignal(std::string("Read data failed."));
                break;
            } else if (len > 0) {
                std::shared_ptr<char> bytes(new char[len], std::default_delete<char[]>());
                memcpy(bytes.get(), data, len);
                bytesRxSignal(std::move(bytes), len, dPtr->portName);
            }

            // Write data...
            for (auto ctx : d->txBytes) {
                auto &bytes = d->txBytes.front();
                int len = serialPortIml->writeData(bytes.first.get(), bytes.second);
                if (len == -1) {
                    errorOccurredSignal(std::string("Write data failed."));
                    break;
                } else {
                    bytesTxSignal(std::move(bytes.first), len, dPtr->portName);
                }
            }
            d->txBytes.clear();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } else {
        std::string errorString(serialPortIml->getLastErrorMsg());
        errorOccurredSignal(std::string("Open port failed.") + errorString);
    }

    serialPortIml->close();
    delete serialPortIml;
    d->isRunning.store(false);
}

void SerialPort::Load(const wxToolsJson &parameters)
{
    SerialPortParameterKeys keys;
    d->portName = parameters[keys.portName].get<std::string>();
    d->baudRate = parameters[keys.baudRate].get<int>();
    d->flowControl = static_cast<itas109::FlowControl>(parameters[keys.flowControl].get<int>());
    d->parity = static_cast<itas109::Parity>(parameters[keys.parity].get<int>());
    d->stopBits = static_cast<itas109::StopBits>(parameters[keys.stopBits].get<int>());
    d->dataBits = static_cast<itas109::DataBits>(parameters[keys.dataBits].get<int>());
}

wxToolsJson SerialPort::Save()
{
    wxToolsJson parameters;
    SerialPortParameterKeys keys;
    parameters[keys.portName] = d->portName;
    parameters[keys.baudRate] = d->baudRate;
    parameters[keys.flowControl] = static_cast<int>(d->flowControl);
    parameters[keys.parity] = static_cast<int>(d->parity);
    parameters[keys.stopBits] = static_cast<int>(d->stopBits);
    parameters[keys.dataBits] = static_cast<int>(d->dataBits);
    return parameters;
}
