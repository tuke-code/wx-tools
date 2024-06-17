/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "DataStructure.h"

#include <bitset>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

std::vector<wxString> GetFriendlyTextFormats()
{
    static std::vector<wxString> formats;
    if (formats.empty()) {
        formats.push_back(GetFriendlyTextFormat(TextFormat::Bin));
        formats.push_back(GetFriendlyTextFormat(TextFormat::Oct));
        formats.push_back(GetFriendlyTextFormat(TextFormat::Dec));
        formats.push_back(GetFriendlyTextFormat(TextFormat::Hex));
        formats.push_back(GetFriendlyTextFormat(TextFormat::Ascii));
        formats.push_back(GetFriendlyTextFormat(TextFormat::Utf8));
    }

    return formats;
}

wxString GetFriendlyTextFormat(TextFormat format)
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

std::string DoFormattedText(asio::const_buffer &buffer, TextFormat format)
{
    const auto *dataPtr = static_cast<const unsigned char *>(buffer.data());
    size_t size = buffer.size();
    std::ostringstream stringStream;
    if (format == TextFormat::Bin) {
        for (std::size_t i = 0; i < size; ++i) {
            stringStream << std::bitset<8>(dataPtr[i]).to_string() << " ";
        }
        return stringStream.str();
    } else if (format == TextFormat::Oct) {
        for (std::size_t i = 0; i < size; ++i) {
            stringStream << std::setw(3) << std::setfill('0') << std::oct << dataPtr[i] << " ";
        }
        return stringStream.str();
    } else if (format == TextFormat::Dec) {
        for (std::size_t i = 0; i < size; ++i) {
            stringStream << std::setw(3) << std::setfill('0') << std::dec << dataPtr[i] << " ";
        }
        return stringStream.str();
    } else if (format == TextFormat::Hex) {
        for (std::size_t i = 0; i < size; ++i) {
            stringStream << std::setw(2) << std::setfill('0') << std::hex << dataPtr[i] << " ";
        }
        return stringStream.str();
    } else if (format == TextFormat::Ascii) {
        return std::string(dataPtr, dataPtr + size);
    } else if (format == TextFormat::Utf8) {
        return std::string(dataPtr, dataPtr + size);
    }

    return "formatting error";
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
        typeMap[CommunicationType::WSClient] = wxT("WebSocket Client");
        typeMap[CommunicationType::WSServer] = wxT("WebSocket Server");
    }

    if (typeMap.find(type) == typeMap.end()) {
        return "Unknown";
    } else {
        return typeMap[type];
    }
}
