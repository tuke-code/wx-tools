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

#include "Utilities/BaudRateComboBox.h"
#include "Utilities/DataBitsComboBox.h"
#include "Utilities/FlowBitsComboBox.h"
#include "Utilities/ParityComboBox.h"
#include "Utilities/PortNameComboBox.h"
#include "Utilities/StopBitsComboBox.h"

#include "Links/SerialPort.h"

SerialPortController::SerialPortController(wxWindow *parent)
    : LinksController(parent)
    , m_portNameComboBox(nullptr)
    , m_baudRateComboBox(nullptr)
    , m_dataBitsComboBox(nullptr)
    , m_stopBitsComboBox(nullptr)
    , m_parityComboBox(nullptr)
    , m_flowBitsComboBox(nullptr)
{
    InitPortNameComboBox(wxT("Port name"), 0, parent);
    InitBaudRateComboBox(wxT("Baud rate"), 1, parent);
    InitDataBitsComboBox(wxT("Data bits"), 2, parent);
    InitStopBitsComboBox(wxT("Stop bits"), 3, parent);
    InitParityComboBox(wxT("Parity"), 4, parent);
    InitFlowBitsComboBox(wxT("Flow bits"), 5, parent);

    AddGrowableCol(1);
}

SerialPortController::~SerialPortController() {}

void SerialPortController::Disable()
{
    m_portNameComboBox->Disable();
    m_baudRateComboBox->Disable();
    m_dataBitsComboBox->Disable();
    m_stopBitsComboBox->Disable();
    m_flowBitsComboBox->Disable();
    m_parityComboBox->Disable();
}

void SerialPortController::Enable()
{
    m_portNameComboBox->Enable();
    m_baudRateComboBox->Enable();
    m_dataBitsComboBox->Enable();
    m_stopBitsComboBox->Enable();
    m_flowBitsComboBox->Enable();
    m_parityComboBox->Enable();
}

wxJSONValue SerialPortController::Save() const
{
    wxJSONValue json = wxJSONValue(wxJSONTYPE_OBJECT);
    SerialPortParameterKeys keys;
    json[keys.portName] = m_portNameComboBox->GetPortName();
    json[keys.baudRate] = m_baudRateComboBox->GetBaudRate();
    json[keys.characterSize] = m_dataBitsComboBox->GetDataBits().value();
    json[keys.stopBits] = m_stopBitsComboBox->GetStopBits();
    json[keys.flowControl] = m_flowBitsComboBox->GetFlowBits();
    json[keys.parity] = m_parityComboBox->GetParity();
    return json;
}

void SerialPortController::Load(const wxJSONValue &json)
{
    SerialPortParameterKeys keys;
    wxString portName = json.Get(keys.portName, wxJSONValue()).AsString();
    int baudRate = json.Get(keys.baudRate, wxJSONValue(9600)).AsInt();
    int dataBits = json.Get(keys.characterSize, wxJSONValue(8)).AsInt();
    int stopBits = json.Get(keys.stopBits, wxJSONValue(0)).AsInt();
    int flowBits = json.Get(keys.flowControl, wxJSONValue(0)).AsInt();
    int parity = json.Get(keys.parity, wxJSONValue(0)).AsInt();

    m_portNameComboBox->SetPortName(portName);
    m_baudRateComboBox->SetBaudRate(baudRate);
    m_dataBitsComboBox->SetDataBits(dataBits);
    m_stopBitsComboBox->SetStopBits(stopBits);
    m_flowBitsComboBox->SetFlowBits(flowBits);
    m_parityComboBox->SetParity(parity);
}

Link *SerialPortController::CreateLink()
{
    return new SerialPort();
}

void SerialPortController::AboutToOpen(Link *link)
{
    LinksController::AboutToOpen(link);

#if 0
    wxJSONValue json = link->Save();
    wxString str = json.Dump();
    wxLogInfo(str);
#endif
}

void SerialPortController::InitPortNameComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_portNameComboBox = new PortNameComboBox(parent);
    Add(m_portNameComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitBaudRateComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_baudRateComboBox = new BaudRateComboBox(parent);
    Add(m_baudRateComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitDataBitsComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_dataBitsComboBox = new DataBitsComboBox(parent);
    Add(m_dataBitsComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitStopBitsComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_stopBitsComboBox = new StopBitsComboBox(parent);
    Add(m_stopBitsComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitParityComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_parityComboBox = new ParityComboBox(parent);
    Add(m_parityComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SerialPortController::InitFlowBitsComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_flowBitsComboBox = new FlowBitsComboBox(parent);
    Add(m_flowBitsComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}
