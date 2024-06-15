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

#include "Unit/ComboBox.h"
#include "Unit/TextFormatComboBox.h"

InputControlBox::InputControlBox(wxWindow* parent)
    : wxStaticBoxSizer(wxHORIZONTAL, parent, wxT("Input Control"))
{
    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Cycle"));
    auto cycleInterval = new ComboBox(GetStaticBox());
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Format"));
    auto formatComboBox = new TextFormatComboBox(GetStaticBox());
    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    auto sendingButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Send"));

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(sendingButton, 1, wxEXPAND | wxALL, 0);

    auto* sizer = new wxGridBagSizer(4, 4);
    sizer->Add(cycleText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(cycleInterval, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(formatText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(formatComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(buttonSizer, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    Add(sizer, 1, wxEXPAND | wxALL, 0);

    cycleInterval->Append(wxT("Disabled"));
    for (int i = 10; i <= 100; i += 10) {
        cycleInterval->AppendString(wxString::Format(wxT("%d ms"), i));
    }
    for (int i = 100; i <= 1000; i += 100) {
        cycleInterval->AppendString(wxString::Format(wxT("%d ms"), i));
    }
    for (int i = 2000; i <= 10000; i += 1000) {
        cycleInterval->AppendString(wxString::Format(wxT("%d ms"), i));
    }
    cycleInterval->SetSelection(0);
    cycleInterval->SetEditable(false);
}