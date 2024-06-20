/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio/buffer.hpp>
#include <glog/logging.h>
#include <wx/wx.h>

#define eToolsLog(severity) LOG(severity)

#define LogInfo(info) LOG(INFO) << info
#define LogWarning(warning) LOG(WARNING) << warning
#define LogError(error) LOG(ERROR) << error
void InitGoogleLog(const char *argv0);

std::string currentDateTimeString(const std::string &format = "%Y-%m-%d %H:%M:%S",
                                  bool showMs = false);

enum class TextFormat { Bin, Oct, Dec, Hex, Ascii, Utf8, Unknown = -1 };
std::vector<wxString> GetSuportedTextFormats();
wxString GetTextFormatName(TextFormat format);
std::string DoFormatText(asio::const_buffer &buffer, TextFormat format);
std::string GetBinString(uint8_t value);
std::string GetOctString(uint8_t value);
std::string GetDecString(uint8_t value);
std::string GetHexString(uint8_t value);

enum class CommunicationType {
    SerialPort,
    UDPClient,
    UDPServer,
    TCPClient,
    TCPServer,
    WSClient,
    WSServer,
    Unknown = -1
};
std::vector<CommunicationType> GetSuportedCommunicationTypes();
wxString GetCommunicationName(CommunicationType type);
