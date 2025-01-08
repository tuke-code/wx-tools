/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ParityComboBox.h"

ParityComboBox::ParityComboBox(wxWindow* parent)
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
    Append(wxT("Odd"));
    Append(wxT("Even"));
    SetSelection(0);
}

asio::serial_port_base::parity::type ParityComboBox::GetParity() const
{
    switch (GetSelection()) {
    case 0:
        return asio::serial_port_base::parity::type::none;
    case 1:
        return asio::serial_port_base::parity::type::odd;
    case 2:
        return asio::serial_port_base::parity::type::even;
    default:
        return asio::serial_port_base::parity::type::none;
    }
}

void ParityComboBox::SetParity(int parity)
{
    switch (parity) {
    case asio::serial_port_base::parity::type::none:
        SetSelection(0);
        break;
    case asio::serial_port_base::parity::type::odd:
        SetSelection(1);
        break;
    case asio::serial_port_base::parity::type::even:
        SetSelection(2);
        break;
    default:
        SetSelection(0);
        break;
    }
}
