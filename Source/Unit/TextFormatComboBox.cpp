/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TextFormatComboBox.h"

#include "Common/eTools.h"

TextFormatComboBox::TextFormatComboBox(wxWindow* parent)
    : wxComboBox(parent,
                 wxID_ANY,
                 wxEmptyString,
                 wxDefaultPosition,
                 wxDefaultSize,
                 0,
                 nullptr,
                 wxCB_READONLY)
{
    std::vector<wxString> formats = GetSuportedTextFormats();
    for (const wxString& format : formats) {
        AppendString(format);
    }
    SetSelection(3);
}

TextFormat TextFormatComboBox::GetSelectedFormat() const
{
    int selection = GetCurrentSelection();
    return static_cast<TextFormat>(selection);
}
