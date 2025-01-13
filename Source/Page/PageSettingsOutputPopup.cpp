/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlPanelOutputPopup.h"

#include <wx/gbsizer.h>

ControlPanelOutputPopup::ControlPanelOutputPopup(wxButton *controlButton)
    : Popup(controlButton)
{
    auto panel = new wxPanel(this);

    auto filterLabel = new wxStaticText(panel, wxID_ANY, "Filter");
    auto filterTextCtrl = new wxComboBox(panel, wxID_ANY, "", wxDefaultPosition);
    auto highlightLabel = new wxStaticText(panel, wxID_ANY, "Highlight");
    auto highlightTextCtrl = new wxTextCtrl(panel,
                                            wxID_ANY,
                                            wxEmptyString,
                                            wxDefaultPosition,
                                            wxDefaultSize);

    auto panelSizer = new wxGridBagSizer(4, 4);
    panelSizer->Add(filterLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(filterTextCtrl, wxGBPosition(0, 1), wxDefaultSpan, wxEXPAND);
    panelSizer->Add(highlightLabel, wxGBPosition(1, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(highlightTextCtrl, wxGBPosition(1, 1), wxDefaultSpan, wxEXPAND);
    panelSizer->AddGrowableCol(1);
    panel->SetSizerAndFit(panelSizer);

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 8);
    sizer->SetMinSize(200, -1);
    SetSizerAndFit(sizer);
}
