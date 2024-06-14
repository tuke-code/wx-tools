/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Page.h"

#include "ControlPanel.h"
#include "InputBox.h"
#include "OutputBox.h"

Page::Page(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
{
    auto* sizer = new wxGridSizer(1, 2, 0, 0);
    SetSizerAndFit(sizer);

    auto controlPanel = new ControlPanel(this, wxID_ANY);
    sizer->Add(controlPanel, 0, wxTILE | wxALL, 0);
    sizer->SetItemMinSize(controlPanel, 200, -1);

    auto outputBox = new OutputBox(this, wxID_ANY);
    sizer->Add(outputBox, 1, wxEXPAND | wxALL, 0);

    //auto inputBox = new InputBox(this, wxID_ANY);
    //sizer->Add(inputBox, 0, wxEXPAND | wxDOWN, 0);
}