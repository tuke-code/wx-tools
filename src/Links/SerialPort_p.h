﻿/***************************************************************************************************
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

static void ReadBytes(itas109::CSerialPort *sp, SerialPort *q)
{
    auto d = q->GetD<SerialPortPrivate>();
    char data[wxtDataSize] = {0};
    int len = sp->readAllData(&data);
    if (len == -1) {
        wxThreadEvent *evt = new wxThreadEvent(wxEVT_THREAD, wxtErrorOccurred);
        evt->SetString(_("Read data failed."));
        d->evtHandler->QueueEvent(evt);
    } else if (len > 0) {
        std::shared_ptr<char> bytes(new char[len], std::default_delete<char[]>());
        memcpy(bytes.get(), data, len);

        wxThreadEvent *evt = new wxThreadEvent(wxEVT_THREAD, wxtBytesRx);
        evt->SetPayload<wxtDataItem>(wxtDataItem{std::move(bytes), len, d->portName});
        d->evtHandler->QueueEvent(evt);
    }
}

static void WriteBytes(itas109::CSerialPort *sp, SerialPort *q)
{
    auto d = q->GetD<SerialPortPrivate>();
    d->txBytesLock.lock();
    for (std::pair<std::shared_ptr<char>, int> &ctx : d->txBytes) {
        int len = sp->writeData(ctx.first.get(), ctx.second);
        if (len == -1) {
            wxThreadEvent *evt = new wxThreadEvent(wxEVT_THREAD, wxtErrorOccurred);
            evt->SetString(_("Write data failed."));
            d->evtHandler->QueueEvent(evt);
        } else {
            std::shared_ptr<char> bytes(new char[len], std::default_delete<char[]>());
            memcpy(bytes.get(), ctx.first.get(), len);

            wxThreadEvent *evt = new wxThreadEvent(wxEVT_THREAD, wxtBytesRx);
            evt->SetPayload<wxtDataItem>(wxtDataItem{std::move(bytes), len, d->portName});
            d->evtHandler->QueueEvent(evt);
        }
    }

    d->txBytes.clear();
    d->txBytesLock.unlock();
}
