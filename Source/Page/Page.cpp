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

#include "ControlBoxes.h"
#include "IOPanel.h"

Page::Page(CommunicationType type, wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizerAndFit(sizer);

    auto controlPanelLeft = new ControlBoxes(type, this);
    sizer->Add(controlPanelLeft, 0, wxEXPAND | wxALL, 4);

    auto ioPanelLeft = new IOPanel(this);
    sizer->Add(ioPanelLeft, 1, wxEXPAND | wxALL, 4);
#if 0
    auto ioPanelRight = new IOPanel(this);
    sizer->Add(ioPanelRight, 1, wxEXPAND | wxALL, 4);

    auto controlPanelRight = new ControlPanel(this);
    controlPanelRight->SetMinSize(wxSize(180, -1));
    sizer->Add(controlPanelRight, 0, wxEXPAND | wxALL, 4);
#endif
}
