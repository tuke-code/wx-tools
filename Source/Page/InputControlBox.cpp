/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "InputControlBox.h"

#include <wx/gbsizer.h>
#include <wx/wx.h>

InputControlBox::InputControlBox(wxWindow* parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Input Control"))
{
    auto* sizer = new wxGridBagSizer(4, 4);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, _("Cycle:"));
    sizer->Add(cycleText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cycleInterval = new wxComboBox(GetStaticBox(), wxID_ANY);
    cycleInterval->Append("1");
    cycleInterval->Append("2");
    sizer->Add(cycleInterval, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, _("Format:"));
    sizer->Add(formatText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto formatComboBox = new wxComboBox(GetStaticBox(), wxID_ANY);
    formatComboBox->Append("1");
    sizer->Add(formatComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, _("Settings"));
    buttonSizer->Add(settingsButton, 0, wxEXPAND | wxALL, 0);

    auto sendingButton = new wxButton(GetStaticBox(), wxID_ANY, _("Send"));
    buttonSizer->Add(sendingButton, 0, wxEXPAND | wxALL, 0);

    sizer->Add(buttonSizer, wxGBPosition(2, 0), wxGBSpan(1, 2));
}