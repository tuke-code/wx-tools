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
#include <wx/wx.h>

enum class TextFormat { Bin, Oct, Dec, Hex, Ascii, Utf8, Unknown = -1 };
std::vector<wxString> GetFriendlyTextFormats();
wxString GetFriendlyTextFormat(TextFormat format);
std::string DoFormattedText(asio::const_buffer &buffer, TextFormat format);

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
