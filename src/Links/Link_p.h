﻿/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <vector>

#include <wx/timer.h>

#include "Link.h"

class LinkPrivate
{
public:
    LinkPrivate()
        : evtHandler(nullptr)
    {}

    std::atomic_bool ignoreCloseError{false};
    std::atomic<bool> enableExitThread{false}; // The flag must be set to true on ui thread.
    std::mutex txBytesLock;
    std::vector<std::pair<std::shared_ptr<char> /*data*/, int /*len*/>> txBytes;
    wxEvtHandler *evtHandler; // You must set this to receive events if you want to use them.

public:
    void DoTryToQueueRxBytes(std::shared_ptr<char> bytes, int len, const wxString &from)
    {
        DoTryToQueueBytes(bytes, len, from, wxtBytesRx);
    }

    void DoTryToQueueTxBytes(std::shared_ptr<char> bytes, int len, const wxString &to)
    {
        DoTryToQueueBytes(bytes, len, to, wxtBytesTx);
    }

    void DoTryToQueueBytes(std::shared_ptr<char> bytes, int len, const wxString &flag, int id)
    {
        if (bytes && evtHandler && len > 0) {
            auto *evt = new wxThreadEvent(wxEVT_THREAD, id);
            evt->SetPayload<wxtDataItem>(wxtDataItem{bytes, len, flag.ToStdString()});
            evtHandler->QueueEvent(evt);
        }
    }

    void DoTryToQueueError(const wxString &error)
    {
        if (evtHandler) {
            auto *evt = new wxThreadEvent(wxEVT_THREAD, wxtErrorOccurred);
            if (ignoreCloseError) {
                evt->SetInt(wxtIgnoreCloseErrorPopup);
            } else {
                evt->SetInt(0);
            }
            evt->SetString(error);
            evtHandler->QueueEvent(evt);
        }
    }
};
