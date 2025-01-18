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
#include "SerialPort.h"

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

void SerialPortLoop(SerialPortPrivate *d, SerialPort *serialPort)
{
    d->invokedInterrupted.store(false);
    auto *serialPortIml = new itas109::CSerialPort();
    serialPortIml->init(d->portName.c_str(),
                        d->baudRate,
                        d->parity,
                        d->dataBits,
                        d->stopBits,
                        d->flowControl);

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
                serialPort->errorOccurredSignal(std::string("Read data failed."));
                break;
            } else if (len > 0) {
                std::shared_ptr<char> bytes(new char[len], std::default_delete<char[]>());
                memcpy(bytes.get(), data, len);
                serialPort->bytesRxSignal(std::move(bytes), len, d->portName);
            }

            // Write data...
            for (auto ctx : d->txBytes) {
                auto &bytes = d->txBytes.front();
                int len = serialPortIml->writeData(bytes.first.get(), bytes.second);
                if (len == -1) {
                    serialPort->errorOccurredSignal(std::string("Write data failed."));
                    break;
                } else {
                    serialPort->bytesTxSignal(std::move(bytes.first), len, d->portName);
                }
            }
            d->txBytes.clear();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } else {
        std::string errorString(serialPortIml->getLastErrorMsg());
        serialPort->errorOccurredSignal(std::string("Open port failed.") + errorString);
    }

    serialPortIml->close();
    delete serialPortIml;
    d->isRunning.store(false);
}
