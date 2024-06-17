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
    : ComboBox(parent)
{
    Append("None");
    Append("Hardware");
    Append("Software");
    SetSelection(0);
}

asio::serial_port::flow_control::type FlowBitsComboBox::GetFlowBits()
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