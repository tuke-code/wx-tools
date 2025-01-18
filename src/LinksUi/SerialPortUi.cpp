/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SerialPortUi.h"

#include <wx/gbsizer.h>
#include <wx/string.h>

#include "Utilities/BaudRateComboBox.h"
#include "Utilities/DataBitsComboBox.h"
#include "Utilities/FlowBitsComboBox.h"
#include "Utilities/ParityComboBox.h"
#include "Utilities/PortNameComboBox.h"
#include "Utilities/StopBitsComboBox.h"

#include "Links/SerialPort.h"

SerialPortUi::SerialPortUi(wxWindow *parent)
    : LinkUi(parent)
    , m_portNameComboBox(nullptr)
    , m_baudRateComboBox(nullptr)
    , m_dataBitsComboBox(nullptr)
    , m_stopBitsComboBox(nullptr)
    , m_parityComboBox(nullptr)
    , m_flowBitsComboBox(nullptr)
{
    m_portNameComboBox = new PortNameComboBox(parent);
    m_baudRateComboBox = new BaudRateComboBox(parent);
    m_dataBitsComboBox = new DataBitsComboBox(parent);
    m_stopBitsComboBox = new StopBitsComboBox(parent);
    m_flowBitsComboBox = new FlowBitsComboBox(parent);
    m_parityComboBox = new ParityComboBox(parent);

    SetupComboBox(m_portNameComboBox, wxT("Port name"), 0, parent);
    SetupComboBox(m_baudRateComboBox, wxT("Baud rate"), 1, parent);
    SetupComboBox(m_dataBitsComboBox, wxT("Data bits"), 2, parent);
    SetupComboBox(m_stopBitsComboBox, wxT("Stop bits"), 3, parent);
    SetupComboBox(m_flowBitsComboBox, wxT("Parity"), 4, parent);
    SetupComboBox(m_parityComboBox, wxT("Flow bits"), 5, parent);

    AddGrowableCol(1);
}

SerialPortUi::~SerialPortUi() {}

void SerialPortUi::Disable()
{
    m_portNameComboBox->Disable();
    m_baudRateComboBox->Disable();
    m_dataBitsComboBox->Disable();
    m_stopBitsComboBox->Disable();
    m_flowBitsComboBox->Disable();
    m_parityComboBox->Disable();
}

void SerialPortUi::Enable()
{
    m_portNameComboBox->Enable();
    m_baudRateComboBox->Enable();
    m_dataBitsComboBox->Enable();
    m_stopBitsComboBox->Enable();
    m_flowBitsComboBox->Enable();
    m_parityComboBox->Enable();
}

wxToolsJson SerialPortUi::Save() const
{
    nlohmann::json json = nlohmann::json(nlohmann::json::object());
    SerialPortParameterKeys keys;
    json[keys.portName] = m_portNameComboBox->GetPortName().ToStdString();
    json[keys.baudRate] = static_cast<int>(m_baudRateComboBox->GetBaudRate());
    json[keys.characterSize] = static_cast<int>(m_dataBitsComboBox->GetDataBits());
    json[keys.stopBits] = static_cast<int>(m_stopBitsComboBox->GetStopBits());
    json[keys.flowControl] = static_cast<int>(m_flowBitsComboBox->GetFlowBits());
    json[keys.parity] = static_cast<int>(m_parityComboBox->GetParity());
    return json;
}

void SerialPortUi::Load(const wxToolsJson &json)
{
    SerialPortParameterKeys keys;
    wxString portName = json[keys.portName].template get<std::string>();
    int baudRate = json[keys.baudRate].template get<int>();
    int dataBits = json[keys.characterSize].template get<int>();
    int stopBits = json[keys.stopBits].template get<int>();
    int flowBits = json[keys.flowControl].template get<int>();
    int parity = json[keys.parity].template get<int>();

    m_portNameComboBox->SetPortName(portName);
    m_baudRateComboBox->SetBaudRate(baudRate);
    m_dataBitsComboBox->SetDataBits(static_cast<itas109::DataBits>(dataBits));
    m_stopBitsComboBox->SetStopBits(static_cast<itas109::StopBits>(stopBits));
    m_flowBitsComboBox->SetFlowBits(static_cast<itas109::FlowControl>(flowBits));
    m_parityComboBox->SetParity(static_cast<itas109::Parity>(parity));
}

Link *SerialPortUi::CreateLink()
{
    return new SerialPort();
}

void SerialPortUi::SetupComboBox(wxComboBox *cb, const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}
