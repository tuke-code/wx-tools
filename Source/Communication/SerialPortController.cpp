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

SerialPortController::SerialPortController(wxWindow *parent)
    : CommunicationController(parent)
{
    Add(new wxStaticText(parent, wxID_ANY, "Port name"),
        wxGBPosition(0, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL);
    Add(new wxComboBox(parent, wxID_ANY), wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL);
    Add(new wxStaticText(parent, wxID_ANY, "Baud rate"),
        wxGBPosition(1, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL);
    Add(new wxComboBox(parent, wxID_ANY), wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL);
    Add(new wxStaticText(parent, wxID_ANY, "Data bits"),
        wxGBPosition(2, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL);
    Add(new wxComboBox(parent, wxID_ANY), wxGBPosition(2, 1), wxGBSpan(1, 1), wxEXPAND | wxALL);
    Add(new wxStaticText(parent, wxID_ANY, "Parity"),
        wxGBPosition(3, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL);
    Add(new wxComboBox(parent, wxID_ANY, ""), wxGBPosition(3, 1), wxGBSpan(1, 0), wxEXPAND | wxALL);
    Add(new wxStaticText(parent, wxID_ANY, "Stop bits"),
        wxGBPosition(4, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL);
    Add(new wxComboBox(parent, wxID_ANY, ""), wxGBPosition(4, 1), wxGBSpan(1, 1), wxEXPAND | wxALL);
    Add(new wxStaticText(parent, wxID_ANY, "Flow control"),
        wxGBPosition(5, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL);
    Add(new wxComboBox(parent, wxID_ANY, ""), wxGBPosition(5, 1), wxGBSpan(1, 1), wxEXPAND | wxALL);
}

SerialPortController::~SerialPortController() {}
