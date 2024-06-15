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

ControlPanel::ControlPanel(CommunicationType type, wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);

    auto communicationControlBox = new CommunicationControlBox(type, this);
    sizer->Add(communicationControlBox, 1, wxEXPAND | wxALL);

    auto outputControlBox = new OutputControlBox(this);
    sizer->Add(outputControlBox, 1, wxEXPAND | wxALL);

    sizer->Add(new wxStaticText(this, wxID_ANY, wxT("")), 1, wxEXPAND);

    auto inputControlBox = new InputControlBox(this);
    sizer->Add(inputControlBox, 1, wxEXPAND | wxALL);
}
