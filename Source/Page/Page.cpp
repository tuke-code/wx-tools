/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Page.h"
#include "OutputBox.h"

Page::Page(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
{
    wxGridSizer* sizer = new wxGridSizer(1, 1, 0, 0);
    SetSizer(sizer);

    auto outputBox = new OutputBox(this, wxID_ANY);
    sizer->Add(outputBox, 0, wxEXPAND | wxALL, 0);
}