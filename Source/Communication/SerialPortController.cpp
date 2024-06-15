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
    auto AddLabel = [=](const wxString &label, int row, int col) -> wxSizerItem * {
        auto text = new wxStaticText(parent, wxID_ANY, label);
        return Add(text, wxGBPosition(row, col), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    };

    auto AddComboBox = [=](int row, int col) -> wxSizerItem * {
        auto cb = new wxComboBox(parent, wxID_ANY);
        cb->SetEditable(false);
        return Add(cb, wxGBPosition(row, col), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    };

    AddLabel(wxT("Port name"), 0, 0);
    AddComboBox(0, 1);
    AddLabel(wxT("Baud rate"), 1, 0);
    AddComboBox(1, 1);
    AddLabel(wxT("Data bits"), 2, 0);
    AddComboBox(2, 1);
    AddLabel(wxT("Stop bits"), 3, 0);
    AddComboBox(3, 1);
    AddLabel(wxT("Parity"), 4, 0);
    AddComboBox(4, 1);
    AddLabel(wxT("Flow Control"), 5, 0);
    AddComboBox(5, 1);
}

SerialPortController::~SerialPortController() {}
