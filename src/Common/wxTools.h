/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <glog/logging.h>
#include <nlohmann/json.hpp>
#include <sigslot/signal.hpp>
#include <wx/wx.h>

//--------------------------------------------------------------------------------------------------
// Common
#define wxToolsNone -1
#define wxToolsOk 0
#define wxToolsUnknown -2

#define wxToolsNoneStr wxT("None")
#define wxToolsOkStr wxT("Ok")
#define wxToolsUnknownStr wxT("Unknown")

//--------------------------------------------------------------------------------------------------
// Google Log
#define wxToolsLog(severity) LOG(severity)
#define wxToolsInfo() LOG(INFO)
#define wxToolsWarning() LOG(WARNING)
#define wxToolError() LOG(ERROR)
void DoInitLogging(const char *argv0);
void DoShutdownLogging();

//--------------------------------------------------------------------------------------------------
// json
typedef nlohmann::json wxToolsJson;

//--------------------------------------------------------------------------------------------------
// sigslot
#define wxToolsSignal sigslot::signal

//--------------------------------------------------------------------------------------------------
// libcrc
enum class CRCType {
    CRC_8,
    CRC_16,
    CRC_MODBUS,
    CRC_XMODEM,
    CRC_CCITT_1D0F,
    CRC_CCITT_FFFF,
    CRC_KERMIT,
    CRC_SICK,
    CRC_DNP,
    CRC_32,
    CRC_64_ECMA,
    CRC_64_WE,
};
std::vector<CRCType> GetSuportedCrcTypes();
wxString GetCrcName(CRCType type);

//--------------------------------------------------------------------------------------------------
// Common interface
std::string GetDateTimeString(const std::string &format = "%Y-%m-%d %H:%M:%S", bool showMs = false);

//--------------------------------------------------------------------------------------------------
// Text format
enum class TextFormat { Bin, Oct, Dec, Hex, Ascii, Utf8, Unknown = -1 };
std::vector<int> GetSuportedFormats();
std::vector<wxString> GetSuportedTextFormats();
wxString GetTextFormatName(TextFormat format);
std::string DoDecodeBytes(const std::shared_ptr<char> &bytes, int &len, int format);
std::shared_ptr<char> DoEncodeBytes(const std::string &text, int &len, int format);
std::string GetBinString(uint8_t value);
std::string GetOctString(uint8_t value);
std::string GetDecString(uint8_t value);
std::string GetHexString(uint8_t value);

//--------------------------------------------------------------------------------------------------
// Text format
enum class LinkType {
    SerialPort,
    UDPClient,
    UDPServer,
    TCPClient,
    TCPServer,
    WSClient,
    WSServer,
    Unknown = -1
};
std::vector<LinkType> GetSuportedCommunicationTypes();
wxString GetCommunicationName(LinkType type);

//--------------------------------------------------------------------------------------------------
// Addition
enum class AdditionType { R, RN, N, NR, None = wxToolsNone };
std::vector<AdditionType> GetSuportedAdditionTypes();
wxString GetAdditionName(AdditionType type);

//--------------------------------------------------------------------------------------------------
// Escape character
enum class EscapeType { R, RN, N, NR, R_N, None = wxToolsNone };
std::vector<EscapeType> GetSuportedEscapeTypes();
wxString GetEscapeName(EscapeType type);

//--------------------------------------------------------------------------------------------------
// wxWidgets
void wxToolsSetComboBoxSectionByIntClientData(wxComboBox *comboBox, int clientDataValue);
wxString wxToolsGetSettingsPath();
wxString wxToolsGetSettingsFileName();
std::string DoEncodeFlag(const std::string &ip, uint16_t port);
std::pair<std::string, uint16_t> DoDecodeFlag(const std::string &flag);
