/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "OutputControlBox.h"

#include <wx/gbsizer.h>

#include "Common/TextFormatComboBox.h"

OutputControlBox::OutputControlBox(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Output Control"))
{
    auto *sizer = new wxGridBagSizer(4, 4);
    Add(sizer, 1, wxEXPAND | wxALL, 0);

    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, _("Format:"));
    auto formatComboBox = new TextFormatComboBox(GetStaticBox());
    auto optionsSizer = new wxGridBagSizer(4, 4);
    auto AddCheckBox = [=](const wxString &label, int row, int col) -> wxSizerItem * {
        auto cb = new wxCheckBox(GetStaticBox(), wxID_ANY, label);
        return optionsSizer->Add(cb, wxGBPosition(row, col), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    };

    AddCheckBox(wxT("Rx"), 0, 0);
    AddCheckBox(wxT("Tx"), 0, 1);
    AddCheckBox(wxT("Wrap"), 0, 2);
    AddCheckBox(wxT("Date"), 1, 0);
    AddCheckBox(wxT("Time"), 1, 1);
    AddCheckBox(wxT("MS"), 1, 2);
    AddCheckBox(wxT("Flags"), 2, 0);
    AddCheckBox(wxT("Logs"), 2, 1);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, _("Settings"));
    auto clearButton = new wxButton(GetStaticBox(), wxID_ANY, _("Clear"));
    auto buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(settingsButton, 1, wxALL, 0);
    buttonsSizer->Add(clearButton, 1, wxALL, 0);

    sizer->Add(formatText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(formatComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(optionsSizer, wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    sizer->Add(buttonsSizer, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
}