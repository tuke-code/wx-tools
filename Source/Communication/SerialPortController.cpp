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

#include "Common/BaudRateComboBox.h"
#include "Common/ComboBox.h"
#include "Common/DataBitsComboBox.h"
#include "Common/FlowBitsComboBox.h"
#include "Common/ParityComboBox.h"
#include "Common/PortNameComboBox.h"
#include "Common/StopBitsComboBox.h"

SerialPortController::SerialPortController(wxWindow *parent)
    : CommunicationController(parent)
{
    InitPortNameComboBox(wxT("Port name"), 0, parent);
    InitBaudRateComboBox(wxT("Baud rate"), 1, parent);
    InitDataBitsComboBox(wxT("Data bits"), 2, parent);
    InitStopBitsComboBox(wxT("Stop bits"), 3, parent);
    InitParityComboBox(wxT("Parity"), 4, parent);
    InitFlowBitsComboBox(wxT("Flow bits"), 5, parent);
}

SerialPortController::~SerialPortController() {}

void SerialPortController::InitPortNameComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new PortNameComboBox(parent);
    cb->SetEditable(false);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitBaudRateComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new BaudRateComboBox(parent);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitDataBitsComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new DataBitsComboBox(parent);
    cb->SetEditable(false);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitStopBitsComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new StopBitsComboBox(parent);
    cb->SetEditable(false);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitParityComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new ParityComboBox(parent);
    cb->SetEditable(false);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitFlowBitsComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new FlowBitsComboBox(parent);
    cb->SetEditable(false);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}