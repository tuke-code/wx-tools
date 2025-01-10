/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "CommunicationController.h"

class BaudRateComboBox;
class DataBitsComboBox;
class FlowBitsComboBox;
class ParityComboBox;
class PortNameComboBox;
class StopBitsComboBox;
class SerialPortController : public CommunicationController
{
public:
    SerialPortController(wxWindow *parent = nullptr);
    ~SerialPortController();

    void Disable() override;
    void Enable() override;
    wxJSONValue Save() const override;
    void Load(const wxJSONValue &json) override;

protected:
    HAL_IO *CreateCommunication() override;
    void AboutToOpen(HAL_IO *communication) override;

private:
    void InitPortNameComboBox(const wxString &label, int row, wxWindow *parent);
    void InitBaudRateComboBox(const wxString &label, int row, wxWindow *parent);
    void InitDataBitsComboBox(const wxString &label, int row, wxWindow *parent);
    void InitStopBitsComboBox(const wxString &label, int row, wxWindow *parent);
    void InitParityComboBox(const wxString &label, int row, wxWindow *parent);
    void InitFlowBitsComboBox(const wxString &label, int row, wxWindow *parent);

private:
    PortNameComboBox *m_portNameComboBox;
    BaudRateComboBox *m_baudRateComboBox;
    DataBitsComboBox *m_dataBitsComboBox;
    StopBitsComboBox *m_stopBitsComboBox;
    FlowBitsComboBox *m_flowBitsComboBox;
    ParityComboBox *m_parityComboBox;

private:
    struct ParameterNames
    {
        const wxString portName{"PortName"};
        const wxString baudRate{"BaudRate"};
        const wxString dataBits{"DataBits"};
        const wxString stopBits{"StopBits"};
        const wxString flowBits{"FlowBits"};
        const wxString parity{"Parity"};
    } m_parameterNames;
};
