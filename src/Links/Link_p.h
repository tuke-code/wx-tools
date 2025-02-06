/***************************************************************************************************
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
#include <string>
#include <vector>

#include <wx/timer.h>

#include "Common/wxTools.h"

class LinkPrivate
{
public:
    LinkPrivate()
        : invokedInterrupted(false)
        , isRunning(false)
    {}

    std::atomic_bool invokedInterrupted;
    std::atomic_bool isRunning;

    std::mutex txBytesLock;
    std::vector<std::pair<std::shared_ptr<char> /*data*/, int /*len*/>> txBytes; // bytes to send

    std::mutex errorMessagesLock;
    std::string errorMessage; // the last error message

    std::mutex bytesRxLock;
    std::vector<WXTDataItem> bytesRx; // bytes received
    std::mutex bytesTxLock;
    std::vector<WXTDataItem> bytesTx; // bytes sent
};
