/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlRtu.h"

#include "Utilities/BaudRateComboBox.h"
#include "Utilities/DataBitsComboBox.h"
#include "Utilities/ParityComboBox.h"
#include "Utilities/PortNameComboBox.h"
#include "Utilities/StopBitsComboBox.h"

namespace Modbus {

ControlRtu::ControlRtu(wxWindow *parent)
    : wxStaticBoxSizer(wxHORIZONTAL, parent, _("Rtu Settings"))
    , m_portNameComboBox(nullptr)
    , m_baudRateComboBox(nullptr)
    , m_dataBitsComboBox(nullptr)
    , m_stopBitsComboBox(nullptr)
    , m_parityComboBox(nullptr)
{
    auto sizer = new wxGridBagSizer(4, 4);
    auto SetupComboBox = [sizer](wxComboBox *cb, const wxString &label, int row, wxWindow *parent) {
        auto text = new wxStaticText(parent, wxID_ANY, label);
        sizer->Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
        sizer->Add(cb, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    };

    m_portNameComboBox = new PortNameComboBox(parent);
    m_baudRateComboBox = new BaudRateComboBox(parent);
    m_dataBitsComboBox = new DataBitsComboBox(parent);
    m_stopBitsComboBox = new StopBitsComboBox(parent);
    m_parityComboBox = new ParityComboBox(parent);

    SetupComboBox(m_portNameComboBox, _("Port name"), 0, parent);
    SetupComboBox(m_baudRateComboBox, _("Baud rate"), 1, parent);
    SetupComboBox(m_dataBitsComboBox, _("Data bits"), 2, parent);
    SetupComboBox(m_stopBitsComboBox, _("Stop bits"), 3, parent);
    SetupComboBox(m_parityComboBox, _("Parity bits"), 4, parent);

    sizer->AddGrowableCol(1);
    Add(sizer, 1, wxEXPAND | wxALL, 0);
}

ControlRtu::~ControlRtu() {}

void ControlRtu::Disable()
{
    m_portNameComboBox->Disable();
    m_baudRateComboBox->Disable();
    m_dataBitsComboBox->Disable();
    m_stopBitsComboBox->Disable();
    m_parityComboBox->Disable();
}

void ControlRtu::Enable()
{
    m_portNameComboBox->Enable();
    m_baudRateComboBox->Enable();
    m_dataBitsComboBox->Enable();
    m_stopBitsComboBox->Enable();
    m_parityComboBox->Enable();
}

wxtJson ControlRtu::DoSave() const
{
    nlohmann::json json = nlohmann::json(nlohmann::json::object());
    ControlRtuParameterKeys keys;
    json[keys.portName] = m_portNameComboBox->GetPortName().ToStdString();
    json[keys.baudRate] = static_cast<int>(m_baudRateComboBox->GetBaudRate());
    json[keys.dataBits] = static_cast<int>(m_dataBitsComboBox->GetDataBits());
    json[keys.stopBits] = static_cast<int>(m_stopBitsComboBox->GetStopBits());
    json[keys.parity] = static_cast<int>(m_parityComboBox->GetParity());
    return json;
}

void ControlRtu::DoLoad(const wxtJson &json)
{
    ControlRtuParameterKeys keys;
    // clang-format off
    wxString portName = wxtGetJsonObjValue<std::string>(json, keys.portName, std::string(""));
    int baudRate = wxtGetJsonObjValue<int>(json, keys.baudRate, 9600);
    int dataBits = wxtGetJsonObjValue<int>(json, keys.dataBits, static_cast<int>(itas109::DataBits8));
    int stopBits = wxtGetJsonObjValue<int>(json, keys.stopBits, static_cast<int>(itas109::StopOne));
    int parity = wxtGetJsonObjValue<int>(json, keys.parity, static_cast<int>(itas109::ParityNone));
    // clang-format on

    m_portNameComboBox->SetPortName(portName);
    m_baudRateComboBox->SetBaudRate(baudRate);
    m_dataBitsComboBox->SetDataBits(static_cast<itas109::DataBits>(dataBits));
    m_stopBitsComboBox->SetStopBits(static_cast<itas109::StopBits>(stopBits));
    m_parityComboBox->SetParity(static_cast<itas109::Parity>(parity));
}

} // namespace Modbus
