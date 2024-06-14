/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Page.h"

#include <wx/gbsizer.h>

#include "ControlPanel.h"
#include "IOPanel.h"

Page::Page(wxWindow* parent, wxWindowID id)
    : wxPanel(parent, id)
{
    auto* sizer = new wxGridBagSizer(0, 0);
    SetSizerAndFit(sizer);

    auto controlPanelLeft = new ControlPanel(this);
    sizer->Add(controlPanelLeft, wxGBPosition(0, 0), wxGBSpan(1, 1));

    auto ioPanelLeft = new IOPanel(this);
    sizer->Add(ioPanelLeft, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto ioPanelRight = new IOPanel(this);
    sizer->Add(ioPanelRight, wxGBPosition(0, 2), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto controlPanelRight = new ControlPanel(this);
    sizer->Add(controlPanelRight, wxGBPosition(0, 3), wxGBSpan(1, 1));
}