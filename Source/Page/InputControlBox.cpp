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

#include "Common/TextFormatComboBox.h"

InputControlBox::InputControlBox(wxWindow* parent)
    : wxStaticBoxSizer(wxHORIZONTAL, parent, wxT("Input Control"))
{
#if 1
    auto* sizer = new wxGridBagSizer(4, 4);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Cycle"));
    auto cycleInterval = new wxComboBox(GetStaticBox(), wxID_ANY);
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Format"));
    auto formatComboBox = new TextFormatComboBox(GetStaticBox());
    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    auto sendingButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Send"));

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(sendingButton, 1, wxEXPAND | wxALL, 0);

    sizer->Add(cycleText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(cycleInterval, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(formatText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(formatComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(buttonSizer, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
#else
    auto sizer = new wxGridSizer(3, 2, 4, 4);
    Add(sizer, 1, wxEXPAND | wxALL, 0);

    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Cycle"));
    auto cycleInterval = new wxComboBox(GetStaticBox(), wxID_ANY);
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Format"));
    auto formatComboBox = new TextFormatComboBox(GetStaticBox());
    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    auto sendingButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Send"));

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(sendingButton, 1, wxEXPAND | wxALL, 0);

    sizer->Add(cycleText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(cycleInterval, 0, wxEXPAND | wxALL, 0);
    sizer->Add(formatText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(formatComboBox, 0, wxEXPAND | wxALL, 0);
    sizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 0);
#endif
}