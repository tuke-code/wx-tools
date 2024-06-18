/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Interface.h"

#include <chrono>
#include <iomanip>
#include <iostream>

std::string currentDateTimeString(const std::string &format, bool showMs)
{
    auto now = std::chrono::system_clock::now();
    auto nowTime = std::chrono::system_clock::to_time_t(now);
    auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count()
                 % 1000;
    std::tm *tm = std::localtime(&nowTime);
    char buffer[80] = {0};
    if (showMs) {
        std::strftime(buffer, 80, format.c_str(), tm);
        return std::string(buffer) + "." + std::to_string(nowMs);
    } else {
        std::strftime(buffer, 80, format.c_str(), tm);
        return std::string(buffer);
    }
}