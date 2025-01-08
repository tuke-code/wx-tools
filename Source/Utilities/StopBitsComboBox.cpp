/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "StopBitsComboBox.h"

StopBitsComboBox::StopBitsComboBox(wxWindow* parent)
    : wxComboBox(parent,
                 wxID_ANY,
                 wxEmptyString,
                 wxDefaultPosition,
                 wxDefaultSize,
                 0,
                 nullptr,
                 wxCB_READONLY)
{
    Append("1");
    Append("1.5");
    Append("2");
    SetSelection(0);
}

asio::serial_port::stop_bits::type StopBitsComboBox::GetStopBits() const
{
    switch (GetSelection()) {
    case 0:
        return asio::serial_port::stop_bits::one;
    case 1:
        return asio::serial_port::stop_bits::onepointfive;
    case 2:
        return asio::serial_port::stop_bits::two;
    default:
        return asio::serial_port::stop_bits::one;
    }
}

void StopBitsComboBox::SetStopBits(int stopBits)
{
    switch (stopBits) {
    case asio::serial_port::stop_bits::one:
        SetStringSelection("1");
        break;
    case asio::serial_port::stop_bits::onepointfive:
        SetStringSelection("1.5");
        break;
    case asio::serial_port::stop_bits::two:
        SetStringSelection("2");
        break;
    default:
        SetStringSelection("1");
        break;
    }
}
