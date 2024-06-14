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
#include "InputBox.h"
#include "OutputBox.h"

ControlPanel::ControlPanel(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);

    auto communicationControlBox = new CommunicationControlBox(this);
    sizer->Add(communicationControlBox);

    auto outputBox = new OutputBox(this, wxID_ANY);
    sizer->Add(outputBox);

    //sizer.add(new wxStaticText(this, wxID_ANY, ""), 0, wxEXPAND, 0);

    auto inputBox = new InputBox(this, wxID_ANY);
    sizer->Add(inputBox, 0, wxEXPAND | wxDOWN, 0);
}