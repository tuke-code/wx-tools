/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/gbsizer.h>
#include <wx/wx.h>

#include "Common/wxTools.h"

class BaudRateComboBox;
class DataBitsComboBox;
class ParityComboBox;
class PortNameComboBox;
class StopBitsComboBox;

namespace Modbus {

struct ControlRtuParameterKeys
{
    const std::string portName{"portName"};
    const std::string baudRate{"baudRate"};
    const std::string parity{"parity"};
    const std::string stopBits{"stopBits"};
    const std::string dataBits{"dataBits"};
};

class ControlRtu : public wxStaticBoxSizer
{
public:
    ControlRtu(wxWindow *parent);
    ~ControlRtu();

    void Disable();
    void Enable();
    wxtJson DoSave() const;
    void DoLoad(const wxtJson &json);

private:
    PortNameComboBox *m_portNameComboBox;
    BaudRateComboBox *m_baudRateComboBox;
    DataBitsComboBox *m_dataBitsComboBox;
    StopBitsComboBox *m_stopBitsComboBox;
    ParityComboBox *m_parityComboBox;
};

} // namespace Modbus
