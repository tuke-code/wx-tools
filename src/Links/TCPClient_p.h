/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>
#include <mutex>

#include "SocketClient_p.h"

class TCPClientPrivate : public SocketClientPrivate
{
public:
    std::vector<std::pair<std::string, int>> msgList;
    std::mutex msgMutex;
};
