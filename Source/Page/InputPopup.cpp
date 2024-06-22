/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "InputPopup.h"

#include <wx/gbsizer.h>
#include <wx/popupwin.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>

#include "Unit/AdditionBoxSizer.h"
#include "Unit/CRCTypeComboBox.h"
#include "Unit/ESCBoxSizer.h"

InputPopup::InputPopup(wxButton *controlButton)
    : Popup(controlButton, false)
{
    auto panel = new wxPanel(this);
    auto prefixLabel = new wxStaticText(panel, wxID_ANY, wxT("Prefix"));
    auto prefixComboBox = new AdditionBoxSizer(panel);
    auto suffixLabel = new wxStaticText(panel, wxID_ANY, wxT("Suffix"));
    auto suffixComboBox = new AdditionBoxSizer(panel);
    auto escLabel = new wxStaticText(panel, wxID_ANY, wxT("ESC"));
    auto escComboBox = new ESCBoxSizer(panel);

    auto startIndexLabel = new wxStaticText(panel, wxID_ANY, wxT("Start Index"));
    auto startIndexSpinCtrl = new wxSpinCtrl(panel, wxID_ANY);
    auto endIndexLabel = new wxStaticText(panel, wxID_ANY, wxT("End Index"));
    auto endIndexSpinCtrl = new wxSpinCtrl(panel, wxID_ANY);
    auto algorithmLabel = new wxStaticText(panel, wxID_ANY, wxT("Algorithm"));
    auto algorithmComboBox = new CRCTypeComboBox(panel);
    auto addCrcCheckBox = new wxCheckBox(panel, wxID_ANY, wxT("Add CRC"));
    auto bigEndianCheckBox = new wxCheckBox(panel, wxID_ANY, wxT("Big Endian"));

    auto sizer = new wxGridBagSizer(4, 4);
    sizer->Add(prefixLabel, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(prefixComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(suffixLabel, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(suffixComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(escLabel, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(escComboBox, wxGBPosition(2, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto line = new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    sizer->Add(line, wxGBPosition(3, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);

    // clang-format off
    sizer->Add(startIndexLabel, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(startIndexSpinCtrl, wxGBPosition(4, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(endIndexLabel, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(endIndexSpinCtrl, wxGBPosition(5, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(algorithmLabel, wxGBPosition(6, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(algorithmComboBox, wxGBPosition(6, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(addCrcCheckBox, 1, wxEXPAND | wxALL, 0);
    hSizer->Add(bigEndianCheckBox, 1, wxEXPAND | wxALL, 0);
    sizer->Add(hSizer, wxGBPosition(7, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    // clang-format on

    sizer->AddGrowableCol(1);
    panel->SetMinSize(wxSize(152, -1));
    panel->SetSizerAndFit(sizer);

    int padding = 8;
    auto panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(panel, 1, wxEXPAND | wxALL, padding);
    SetSizerAndFit(panelSizer);
}