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

#include "Common/wxTools.h"
#include "SerialPort.h"

SerialPortController::SerialPortController(wxWindow *parent)
    : CommunicationController(parent)
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

nlohmann::json SerialPortController::SaveParameters() const
{
    nlohmann::json json;
    json[m_parameterNames.portName] = m_portNameComboBox->GetPortName().ToStdString();
    json[m_parameterNames.baudRate] = m_baudRateComboBox->GetBaudRate();
    json[m_parameterNames.dataBits] = m_dataBitsComboBox->GetDataBits().value();
    json[m_parameterNames.stopBits] = m_stopBitsComboBox->GetStopBits();
    json[m_parameterNames.flowBits] = m_flowBitsComboBox->GetFlowBits();
    json[m_parameterNames.parity] = m_parityComboBox->GetParity();
    return json;
}

void SerialPortController::LoadParameters(const nlohmann::json &json)
{
    m_portNameComboBox->SetPortName(json[m_parameterNames.portName]);
    m_baudRateComboBox->SetBaudRate(json[m_parameterNames.baudRate]);
    m_dataBitsComboBox->SetDataBits(json[m_parameterNames.dataBits]);
    m_stopBitsComboBox->SetStopBits(json[m_parameterNames.stopBits]);
    m_flowBitsComboBox->SetFlowBits(json[m_parameterNames.flowBits]);
    m_parityComboBox->SetParity(json[m_parameterNames.parity]);
}

Communication *SerialPortController::CreateCommunication()
{
    return new SerialPort();
}

void SerialPortController::AboutToOpen(Communication *communication)
{
    auto serialPort = dynamic_cast<SerialPort *>(communication);
    if (!serialPort) {
        return;
    }

    const wxString portName = m_portNameComboBox->GetValue();
    int baudRate = m_baudRateComboBox->GetBaudRate();
    asio::serial_port::character_size dataBits = m_dataBitsComboBox->GetDataBits();
    asio::serial_port::stop_bits::type stopBits = m_stopBitsComboBox->GetStopBits();
    asio::serial_port::parity::type parity = m_parityComboBox->GetParity();
    asio::serial_port::flow_control::type flowControl = m_flowBitsComboBox->GetFlowBits();

    auto info = wxString::Format("Open serial port, port name: %s, baud rate: %d, data bits: %d, "
                                 "stop bits: %d, parity: %d, flow control: %d",
                                 portName,
                                 static_cast<int>(baudRate),
                                 dataBits.value(),
                                 static_cast<int>(stopBits),
                                 static_cast<int>(parity),
                                 static_cast<int>(flowControl));
    wxToolsInfo() << info;

    serialPort->SetBaudRate(baudRate);
    serialPort->SetCharacterSize(dataBits);
    serialPort->SetFlowControl(flowControl);
    serialPort->SetParity(parity);
    serialPort->SetStopBits(stopBits);
    serialPort->SetPortName(portName.ToStdString());
}

void SerialPortController::AboutToClose(Communication *communication) {}

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
