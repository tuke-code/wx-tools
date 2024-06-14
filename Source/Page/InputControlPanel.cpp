/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "InputControlBox.h"

InputControlPanel::InputControlPanel(wxWindow* parent)
    : wxPanel(wxVERTICAL, parent)
{
    auto* sizer = new wxGridSizer(wxHORIZONTAL);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    auto cycleText = new wxStaticText(this, wxID_ANY, _("Cycle:"));
    sizer->Add(cycleText, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cycleInterval = new wxComboBox(this, wxID_ANY);
    cycleInterval->Append("1");
    cycleInterval->Append("2");
    sizer->Add(cycleInterval, 0, wxALIGN_CENTER_VERTICAL | wxALL, 0);
}