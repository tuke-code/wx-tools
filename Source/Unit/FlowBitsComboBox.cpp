/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "FlowBitsComboBox.h"

FlowBitsComboBox::FlowBitsComboBox(wxWindow* parent)
    : wxComboBox(parent,
                 wxID_ANY,
                 wxEmptyString,
                 wxDefaultPosition,
                 wxDefaultSize,
                 0,
                 nullptr,
                 wxCB_READONLY)
{
    Append(wxT("None"));
    Append(wxT("Hardware"));
    Append(wxT("Software"));
    SetSelection(0);
}

asio::serial_port::flow_control::type FlowBitsComboBox::GetFlowBits() const
{
    switch (GetSelection()) {
    case 0:
        return asio::serial_port::flow_control::none;
    case 1:
        return asio::serial_port::flow_control::hardware;
    case 2:
        return asio::serial_port::flow_control::software;
    default:
        return asio::serial_port::flow_control::none;
    }
}

void FlowBitsComboBox::SetFlowBits(int flowBits)
{
    switch (flowBits) {
    case asio::serial_port::flow_control::none:
        SetSelection(0);
        break;
    case asio::serial_port::flow_control::hardware:
        SetSelection(1);
        break;
    case asio::serial_port::flow_control::software:
        SetSelection(2);
        break;
    default:
        SetSelection(0);
        break;
    }
}
