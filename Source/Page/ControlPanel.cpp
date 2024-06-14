/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlPanel.h"

#include <wx/stattext.h>

#include "CommunicationControlBox.h"
#include "InputControlBox.h"
#include "OutputControlBox.h"

ControlPanel::ControlPanel(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);

    auto communicationControlBox = new CommunicationControlBox(this);
    sizer->Add(communicationControlBox, 0, wxEXPAND | wxALL, 0);

    auto outputControlBox = new OutputControlBox(this);
    sizer->Add(outputControlBox, 0, wxEXPAND | wxALL, 0);

    //sizer.add(new wxStaticText(this, wxID_ANY, ""), 0, wxEXPAND, 0);

    auto inputControlBox = new InputControlBox(this);
    sizer->Add(inputControlBox, 0, wxEXPAND | wxDOWN, 0);
}