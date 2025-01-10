/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "LinksController.h"

class BaudRateComboBox;
class DataBitsComboBox;
class FlowBitsComboBox;
class ParityComboBox;
class PortNameComboBox;
class StopBitsComboBox;
class SerialPortController : public LinksController
{
public:
    SerialPortController(wxWindow *parent = nullptr);
    ~SerialPortController();

    void Disable() override;
    void Enable() override;
    nlohmann::json Save() const override;
    void Load(const nlohmann::json &json) override;

protected:
    Link *CreateLink() override;
    void AboutToOpen(Link *link) override;

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
};
