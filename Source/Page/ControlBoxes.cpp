/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlBoxes.h"

#include <wx/stattext.h>

#include "CommunicationControlBox.h"
#include "InputControlBox.h"
#include "OutputControlBox.h"

ControlBoxes::ControlBoxes(CommunicationType type, wxWindow* parent)
    : wxBoxSizer(wxVERTICAL)
{
    auto communicationControlBox = new CommunicationControlBox(type, parent);
    Add(communicationControlBox, 0, wxEXPAND | wxALL);

    auto outputControlBox = new OutputControlBox(parent);
    Add(outputControlBox, 0, wxEXPAND | wxALL);

    Add(new wxStaticText(parent, wxID_ANY, wxT("")), 1, wxEXPAND);

    auto inputControlBox = new InputControlBox(parent);
    Add(inputControlBox, 0, wxEXPAND | wxALL);
}
