/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "DataBitsComboBox.h"

DataBitsComboBox::DataBitsComboBox(wxWindow* parent)
    : wxComboBox(parent,
                 wxID_ANY,
                 wxEmptyString,
                 wxDefaultPosition,
                 wxDefaultSize,
                 0,
                 nullptr,
                 wxCB_READONLY)
{
    Append("8");
    Append("7");
    Append("6");
    Append("5");

    SetSelection(0);
}

asio::serial_port::character_size DataBitsComboBox::GetDataBits() const
{
    return static_cast<asio::serial_port::character_size>(wxAtoi(GetStringSelection()));
}

void DataBitsComboBox::SetDataBits(int dataBits)
{
    SetStringSelection(wxString::Format("%d", dataBits));
}
