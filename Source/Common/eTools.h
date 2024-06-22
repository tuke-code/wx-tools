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
#include <sigslot/signal.hpp>
#include <wx/wx.h>

//--------------------------------------------------------------------------------------------------
// Common
#define eToolsNone -1
#define eToolsOk 0
#define eToolsUnknown -2

#define eToolsNoneStr wxT("None")
#define eToolsOkStr wxT("Ok")
#define eToolsUnknownStr wxT("Unknown")

//--------------------------------------------------------------------------------------------------
// Google Log
#define eToolsLog(severity) LOG(severity)
#define eToolsInfo() LOG(INFO)
#define eToolsWarning() LOG(WARNING)
#define eToolError() LOG(ERROR)
void DoInitLogging(const char *argv0);
void DoShutdownLogging();

//--------------------------------------------------------------------------------------------------
// sigslot
#define eToolsSignal sigslot::signal

//--------------------------------------------------------------------------------------------------
// asio
#define eToolsConstBuffer asio::const_buffer

//--------------------------------------------------------------------------------------------------
// Common interface
std::string GetDateTimeString(const std::string &format = "%Y-%m-%d %H:%M:%S", bool showMs = false);

//--------------------------------------------------------------------------------------------------
// Text format
enum class TextFormat { Bin, Oct, Dec, Hex, Ascii, Utf8, Unknown = -1 };
std::vector<wxString> GetSuportedTextFormats();
wxString GetTextFormatName(TextFormat format);
std::string DoDecodeText(eToolsConstBuffer &buffer, TextFormat format);
eToolsConstBuffer DoEncodeText(const std::string &text, TextFormat format);
std::string GetBinString(uint8_t value);
std::string GetOctString(uint8_t value);
std::string GetDecString(uint8_t value);
std::string GetHexString(uint8_t value);

//--------------------------------------------------------------------------------------------------
// Text format
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

//--------------------------------------------------------------------------------------------------
// Addition
enum class AdditionType { R, RN, N, NR, None = eToolsNone };
std::vector<AdditionType> GetSuportedAdditionTypes();
wxString GetAdditionName(AdditionType type);

//--------------------------------------------------------------------------------------------------
// Escape character
enum class EscapeType { R, RN, N, NR, R_N, None = eToolsNone };
std::vector<EscapeType> GetSuportedEscapeTypes();
wxString GetEscapeName(EscapeType type);