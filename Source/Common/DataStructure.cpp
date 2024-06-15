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
        formats.push_back(GetFriendlyTextFormat(TextFormat::System));
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
        formatMap[TextFormat::System] = wxT("System");
    }

    if (formatMap.find(format) == formatMap.end()) {
        return wxT("Unknown");
    } else {
        return formatMap[format];
    }
}