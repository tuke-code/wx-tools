/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SerialPortController.h"

#include <wx/gbsizer.h>

SerialPortController::SerialPortController()
    : CommunicationController()
{
    auto sizer = new wxGridBagSizer(4, 4);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Port name"),
               wxGBPosition(0, 0),
               wxGBSpan(1, 2),
               wxALIGN_CENTER_VERTICAL | wxALL);
    sizer->Add(new wxComboBox(this, wxID_ANY, ""),
               wxGBPosition(0, 2),
               wxGBSpan(1, 2),
               wxEXPAND | wxALL);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Baud rate"),
               wxGBPosition(1, 0),
               wxGBSpan(1, 2),
               wxALIGN_CENTER_VERTICAL | wxALL);
    sizer->Add(new wxComboBox(this, wxID_ANY, ""),
               wxGBPosition(1, 2),
               wxGBSpan(1, 2),
               wxEXPAND | wxALL);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Data bits"),
               wxGBPosition(2, 0),
               wxGBSpan(1, 2),
               wxALIGN_CENTER_VERTICAL | wxALL);
    sizer->Add(new wxComboBox(this, wxID_ANY, ""),
               wxGBPosition(2, 2),
               wxGBSpan(1, 2),
               wxEXPAND | wxALL);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Parity"),
               wxGBPosition(3, 0),
               wxGBSpan(1, 2),
               wxALIGN_CENTER_VERTICAL | wxALL);
    sizer->Add(new wxComboBox(this, wxID_ANY, ""),
               wxGBPosition(3, 2),
               wxGBSpan(1, 2),
               wxEXPAND | wxALL);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Stop bits"),
               wxGBPosition(4, 0),
               wxGBSpan(1, 2),
               wxALIGN_CENTER_VERTICAL | wxALL);
    sizer->Add(new wxComboBox(this, wxID_ANY, ""),
               wxGBPosition(4, 2),
               wxGBSpan(1, 2),
               wxEXPAND | wxALL);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Flow control"),
               wxGBPosition(5, 0),
               wxGBSpan(1, 2),
               wxALIGN_CENTER_VERTICAL | wxALL);
    sizer->Add(new wxComboBox(this, wxID_ANY, ""),
               wxGBPosition(5, 2),
               wxGBSpan(1, 2),
               wxEXPAND | wxALL);

    SetSizerAndFit(sizer);
}

SerialPortController::~SerialPortController() {}
