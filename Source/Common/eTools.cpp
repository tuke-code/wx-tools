﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "eTools.h"

#include <chrono>
#include <map>
#include <sstream>
#include <string>

void FailureWriter(const char *data, size_t size) {}

std::string LogPath()
{
    return "log";
}

void DoInitLogging(const char *argv0)
{
    const std::chrono::minutes keep{7 * 24 * 60};

    google::SetLogFilenameExtension(".log");
    google::EnableLogCleaner(keep);
    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(FailureWriter);

    fLB::FLAGS_logtostdout = false;
    fLB::FLAGS_logtostderr = false;
    fLS::FLAGS_log_dir = LogPath();
    fLI::FLAGS_logbufsecs = 0;
    fLU::FLAGS_max_log_size = 10;
    fLB::FLAGS_stop_logging_if_full_disk = true;
    fLB::FLAGS_colorlogtostderr = true;
#if 0
    fLB::FLAGS_alsologtostderr = true;
#endif
    google::InitGoogleLogging(argv0);
}

void DoShutdownLogging()
{
    google::ShutdownGoogleLogging();
}

std::string GetDateTimeString(const std::string &format, bool showMs)
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

std::string DoDecodeText(asio::const_buffer &buffer, TextFormat format)
{
    const auto *dataPtr = static_cast<const char *>(buffer.data());
    size_t size = buffer.size();

    auto getString = [](const char *data, size_t size, TextFormat format) -> std::string {
        std::ostringstream stringStream;
        for (std::size_t i = 0; i < size; ++i) {
            stringStream << GetString(format, data[i]);
            if (i < size - 1) {
                stringStream << " ";
            }
        }
        return stringStream.str();
    };

    switch (format) {
    case TextFormat::Bin:
    case TextFormat::Oct:
    case TextFormat::Dec:
    case TextFormat::Hex:
        return getString(dataPtr, size, format);
    case TextFormat::Ascii:
        return wxString::FromAscii(dataPtr, size).ToStdString();
    default:
        return wxString::FromUTF8(dataPtr, size).ToStdString();
    }
}

asio::const_buffer DoEncodeText(const std::string &text, TextFormat format)
{
    return asio::buffer(text.data(), text.size());
}

std::string GetBinString(uint8_t value)
{
    static std::vector<std::string> list;
    if (!list.empty()) {
        return list[value];
    }

    list = {"00000000", "00000001", "00000010", "00000011", "00000100", "00000101", "00000110",
            "00000111", "00001000", "00001001", "00001010", "00001011", "00001100", "00001101",
            "00001110", "00001111", "00010000", "00010001", "00010010", "00010011", "00010100",
            "00010101", "00010110", "00010111", "00011000", "00011001", "00011010", "00011011",
            "00011100", "00011101", "00011110", "00011111", "00100000", "00100001", "00100010",
            "00100011", "00100100", "00100101", "00100110", "00100111", "00101000", "00101001",
            "00101010", "00101011", "00101100", "00101101", "00101110", "00101111", "00110000",
            "00110001", "00110010", "00110011", "00110100", "00110101", "00110110", "00110111",
            "00111000", "00111001", "00111010", "00111011", "00111100", "00111101", "00111110",
            "00111111", "01000000", "01000001", "01000010", "01000011", "01000100", "01000101",
            "01000110", "01000111", "01001000", "01001001", "01001010", "01001011", "01001100",
            "01001101", "01001110", "01001111", "01010000", "01010001", "01010010", "01010011",
            "01010100", "01010101", "01010110", "01010111", "01011000", "01011001", "01011010",
            "01011011", "01011100", "01011101", "01011110", "01011111", "01100000", "01100001",
            "01100010", "01100011", "01100100", "01100101", "01100110", "01100111", "01101000",
            "01101001", "01101010", "01101011", "01101100", "01101101", "01101110", "01101111",
            "01110000", "01110001", "01110010", "01110011", "01110100", "01110101", "01110110",
            "01110111", "01111000", "01111001", "01111010", "01111011", "01111100", "01111101",
            "01111110", "01111111", "10000000", "10000001", "10000010", "10000011", "10000100",
            "10000101", "10000110", "10000111", "10001000", "10001001", "10001010", "10001011",
            "10001100", "10001101", "10001110", "10001111", "10010000", "10010001", "10010010",
            "10010011", "10010100", "10010101", "10010110", "10010111", "10011000", "10011001",
            "10011010", "10011011", "10011100", "10011101", "10011110", "10011111", "10100000",
            "10100001", "10100010", "10100011", "10100100", "10100101", "10100110", "10100111",
            "10101000", "10101001", "10101010", "10101011", "10101100", "10101101", "10101110",
            "10101111", "10110000", "10110001", "10110010", "10110011", "10110100", "10110101",
            "10110110", "10110111", "10111000", "10111001", "10111010", "10111011", "10111100",
            "10111101", "10111110", "10111111", "11000000", "11000001", "11000010", "11000011",
            "11000100", "11000101", "11000110", "11000111", "11001000", "11001001", "11001010",
            "11001011", "11001100", "11001101", "11001110", "11001111", "11010000", "11010001",
            "11010010", "11010011", "11010100", "11010101", "11010110", "11010111", "11011000",
            "11011001", "11011010", "11011011", "11011100", "11011101", "11011110", "11011111",
            "11100000", "11100001", "11100010", "11100011", "11100100", "11100101", "11100110",
            "11100111", "11101000", "11101001", "11101010", "11101011", "11101100", "11101101",
            "11101110", "11101111", "11110000", "11110001", "11110010", "11110011", "11110100",
            "11110101", "11110110", "11110111", "11111000", "11111001", "11111010", "11111011",
            "11111100", "11111101", "11111110", "11111111"};

    return list[value];
}

std::string GetOctString(uint8_t value)
{
    static std::vector<std::string> list;
    if (!list.empty()) {
        return list[value];
    }

    list = {"000", "001", "002", "003", "004", "005", "006", "007", "010", "011", "012", "013",
            "014", "015", "016", "017", "020", "021", "022", "023", "024", "025", "026", "027",
            "030", "031", "032", "033", "034", "035", "036", "037", "040", "041", "042", "043",
            "044", "045", "046", "047", "050", "051", "052", "053", "054", "055", "056", "057",
            "060", "061", "062", "063", "064", "065", "066", "067", "070", "071", "072", "073",
            "074", "075", "076", "077", "100", "101", "102", "103", "104", "105", "106", "107",
            "110", "111", "112", "113", "114", "115", "116", "117", "120", "121", "122", "123",
            "124", "125", "126", "127", "130", "131", "132", "133", "134", "135", "136", "137",
            "140", "141", "142", "143", "144", "145", "146", "147", "150", "151", "152", "153",
            "154", "155", "156", "157", "160", "161", "162", "163", "164", "165", "166", "167",
            "170", "171", "172", "173", "174", "175", "176", "177", "200", "201", "202", "203",
            "204", "205", "206", "207", "210", "211", "212", "213", "214", "215", "216", "217",
            "220", "221", "222", "223", "224", "225", "226", "227", "230", "231", "232", "233",
            "234", "235", "236", "237", "240", "241", "242", "243", "244", "245", "246", "247",
            "250", "251", "252", "253", "254", "255", "256", "257", "260", "261", "262", "263",
            "264", "265", "266", "267", "270", "271", "272", "273", "274", "275", "276", "277",
            "300", "301", "302", "303", "304", "305", "306", "307", "310", "311", "312", "313",
            "314", "315", "316", "317", "320", "321", "322", "323", "324", "325", "326", "327",
            "330", "331", "332", "333", "334", "335", "336", "337", "340", "341", "342", "343",
            "344", "345", "346", "347", "350", "351", "352", "353", "354", "355", "356", "357",
            "360", "361", "362", "363", "364", "365", "366", "367", "370", "371", "372", "373",
            "374", "375", "376", "377"};

    return list[value];
}

std::string GetDecString(uint8_t value)
{
    static std::vector<std::string> list;
    if (!list.empty()) {
        return list[value];
    }

    list = {"000", "001", "002", "003", "004", "005", "006", "007", "008", "009", "010", "011",
            "012", "013", "014", "015", "016", "017", "018", "019", "020", "021", "022", "023",
            "024", "025", "026", "027", "028", "029", "030", "031", "032", "033", "034", "035",
            "036", "037", "038", "039", "040", "041", "042", "043", "044", "045", "046", "047",
            "048", "049", "050", "051", "052", "053", "054", "055", "056", "057", "058", "059",
            "060", "061", "062", "063", "064", "065", "066", "067", "068", "069", "070", "071",
            "072", "073", "074", "075", "076", "077", "078", "079", "080", "081", "082", "083",
            "084", "085", "086", "087", "088", "089", "090", "091", "092", "093", "094", "095",
            "096", "097", "098", "099", "100", "101", "102", "103", "104", "105", "106", "107",
            "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119",
            "120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131",
            "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143",
            "144", "145", "146", "147", "148", "149", "150", "151", "152", "153", "154", "155",
            "156", "157", "158", "159", "160", "161", "162", "163", "164", "165", "166", "167",
            "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179",
            "180", "181", "182", "183", "184", "185", "186", "187", "188", "189", "190", "191",
            "192", "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203",
            "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215",
            "216", "217", "218", "219", "220", "221", "222", "223", "224", "225", "226", "227",
            "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239",
            "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251",
            "252", "253", "254", "255"};

    return list[value];
}

std::string GetHexString(uint8_t value)
{
    static std::vector<std::string> list;
    if (!list.empty()) {
        return list[value];
    }

    list = {"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D",
            "0E", "0F", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "1A", "1B",
            "1C", "1D", "1E", "1F", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
            "2A", "2B", "2C", "2D", "2E", "2F", "30", "31", "32", "33", "34", "35", "36", "37",
            "38", "39", "3A", "3B", "3C", "3D", "3E", "3F", "40", "41", "42", "43", "44", "45",
            "46", "47", "48", "49", "4A", "4B", "4C", "4D", "4E", "4F", "50", "51", "52", "53",
            "54", "55", "56", "57", "58", "59", "5A", "5B", "5C", "5D", "5E", "5F", "60", "61",
            "62", "63", "64", "65", "66", "67", "68", "69", "6A", "6B", "6C", "6D", "6E", "6F",
            "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7A", "7B", "7C", "7D",
            "7E", "7F", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "8A", "8B",
            "8C", "8D", "8E", "8F", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99",
            "9A", "9B", "9C", "9D", "9E", "9F", "A0", "A1", "A2", "A3", "A4", "A5", "A6", "A7",
            "A8", "A9", "AA", "AB", "AC", "AD", "AE", "AF", "B0", "B1", "B2", "B3", "B4", "B5",
            "B6", "B7", "B8", "B9", "BA", "BB", "BC", "BD", "BE", "BF", "C0", "C1", "C2", "C3",
            "C4", "C5", "C6", "C7", "C8", "C9", "CA", "CB", "CC", "CD", "CE", "CF", "D0", "D1",
            "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "DA", "DB", "DC", "DD", "DE", "DF",
            "E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "EA", "EB", "EC", "ED",
            "EE", "EF", "F0", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "FA", "FB",
            "FC", "FD", "FE", "FF"};

    return list[value];
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

std::vector<AdditionType> GetSuportedAdditionTypes()
{
    static std::vector<AdditionType> types;
    if (types.empty()) {
        types.push_back(AdditionType::None);
        types.push_back(AdditionType::R);
        types.push_back(AdditionType::RN);
        types.push_back(AdditionType::N);
        types.push_back(AdditionType::NR);
    }

    return types;
}

wxString GetAdditionName(AdditionType type)
{
    static std::map<AdditionType, wxString> typeMap;
    if (typeMap.empty()) {
        typeMap[AdditionType::R] = "\\r";
        typeMap[AdditionType::RN] = "\\r\\n";
        typeMap[AdditionType::N] = "\\n";
        typeMap[AdditionType::NR] = "\\n\\r";
        typeMap[AdditionType::None] = eToolsNoneStr;
    }

    if (typeMap.find(type) == typeMap.end()) {
        return typeMap[AdditionType::None];
    } else {
        return typeMap[type];
    }
}

std::vector<EscapeType> GetSuportedEscapeTypes()
{
    static std::vector<EscapeType> types;
    if (types.empty()) {
        types.push_back(EscapeType::None);
        types.push_back(EscapeType::R);
        types.push_back(EscapeType::RN);
        types.push_back(EscapeType::N);
        types.push_back(EscapeType::NR);
        types.push_back(EscapeType::R_N);
    }

    return types;
}

wxString GetEscapeName(EscapeType type)
{
    static std::map<EscapeType, wxString> typeMap;
    if (typeMap.empty()) {
        typeMap[EscapeType::R] = "\\r";
        typeMap[EscapeType::RN] = "\\r\\n";
        typeMap[EscapeType::N] = "\\n";
        typeMap[EscapeType::NR] = "\\n\\r";
        typeMap[EscapeType::R_N] = "\\r + \\n";
        typeMap[EscapeType::None] = eToolsNoneStr;
    }

    if (typeMap.find(type) == typeMap.end()) {
        return typeMap[EscapeType::None];
    } else {
        return typeMap[type];
    }
}