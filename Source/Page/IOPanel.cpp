/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "IOPanel.h"

#include "InputBox.h"
#include "OutputBox.h"

IOPanel::IOPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);

    auto outputBox = new OutputBox(this);
    sizer->Add(outputBox, 1, wxEXPAND | wxALL, 0);

    auto inputBox = new InputBox(this, wxID_ANY);
    sizer->Add(inputBox, 0, wxEXPAND | wxALL, 0);
}