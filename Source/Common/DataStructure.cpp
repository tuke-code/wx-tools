/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "DataStructure.h"

#include <map>
#include <sstream>
#include <string>

#include "Data.h"

std::vector<wxString> GetSuportedTextFormats()
{
    static std::vector<wxString> formats;
    if (formats.empty()) {
        formats.push_back(GetTextFormatName(TextFormat::Bin));
        formats.push_back(GetTextFormatName(TextFormat::Oct));
        formats.push_back(GetTextFormatName(TextFormat::Dec));
        formats.push_back(GetTextFormatName(TextFormat::Hex));
        formats.push_back(GetTextFormatName(TextFormat::Ascii));
        formats.push_back(GetTextFormatName(TextFormat::Utf8));
    }

    return formats;
}

wxString GetTextFormatName(TextFormat format)
{
    static std::map<TextFormat, wxString> formatMap;
    if (formatMap.empty()) {
        formatMap[TextFormat::Bin] = wxT("Binary");
        formatMap[TextFormat::Oct] = wxT("Octal");
        formatMap[TextFormat::Dec] = wxT("Decimal");
        formatMap[TextFormat::Hex] = wxT("Hexadecimal");
        formatMap[TextFormat::Ascii] = wxT("ASCII");
        formatMap[TextFormat::Utf8] = wxT("UTF-8");
    }

    if (formatMap.find(format) == formatMap.end()) {
        return "Unknown";
    } else {
        return formatMap[format];
    }
}

std::string GetString(TextFormat format, uint8_t value)
{
    if (format == TextFormat::Bin) {
        return GetBinString(value);
    } else if (format == TextFormat::Oct) {
        return GetOctString(value);
    } else if (format == TextFormat::Dec) {
        return GetDecString(value);
    } else if (format == TextFormat::Hex) {
        return GetHexString(value);
    }

    return GetHexString(value);
}

std::string DoFormatText(asio::const_buffer &buffer, TextFormat format)
{
    const auto *dataPtr = static_cast<const char *>(buffer.data());
    size_t size = buffer.size();
    std::ostringstream stringStream;
    switch (format) {
    case TextFormat::Bin:
    case TextFormat::Oct:
    case TextFormat::Dec:
    case TextFormat::Hex:
        for (std::size_t i = 0; i < size; ++i) {
            stringStream << GetString(format, dataPtr[i]);
            if (i < size - 1) {
                stringStream << " ";
            }
        }
        return stringStream.str();
    case TextFormat::Ascii:
        return wxString::FromAscii(dataPtr, size).ToStdString();
    default:
        return wxString::FromUTF8(dataPtr, size).ToStdString();
    }
}

std::vector<CommunicationType> GetSuportedCommunicationTypes()
{
    static std::vector<CommunicationType> types;
    if (types.empty()) {
        types.push_back(CommunicationType::SerialPort);
        types.push_back(CommunicationType::UDPClient);
        types.push_back(CommunicationType::UDPServer);
        types.push_back(CommunicationType::TCPClient);
        types.push_back(CommunicationType::TCPServer);
        types.push_back(CommunicationType::WSClient);
        types.push_back(CommunicationType::WSServer);
    }

    return types;
}

wxString GetCommunicationName(CommunicationType type)
{
    static std::map<CommunicationType, wxString> typeMap;
    if (typeMap.empty()) {
        typeMap[CommunicationType::SerialPort] = wxT("Serial Port");
        typeMap[CommunicationType::UDPClient] = wxT("UDP Client");
        typeMap[CommunicationType::UDPServer] = wxT("UDP Server");
        typeMap[CommunicationType::TCPClient] = wxT("TCP Client");
        typeMap[CommunicationType::TCPServer] = wxT("TCP Server");
        typeMap[CommunicationType::WSClient] = wxT("Web Socket Client");
        typeMap[CommunicationType::WSServer] = wxT("Web Socket Server");
    }

    if (typeMap.find(type) == typeMap.end()) {
        return "Unknown";
    } else {
        return typeMap[type];
    }
}
