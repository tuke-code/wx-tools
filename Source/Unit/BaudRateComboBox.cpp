/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "BaudRateComboBox.h"

BaudRateComboBox::BaudRateComboBox(wxWindow* parent)
    : ComboBox(parent)
{
    Append(wxT("9600"));
    Append(wxT("19200"));
    Append(wxT("38400"));
    Append(wxT("57600"));
    Append(wxT("115200"));
    Append(wxT("230400"));
    Append(wxT("460800"));
    Append(wxT("921600"));

    SetEditable(true);
    SetSelection(0);
}

int BaudRateComboBox::GetBaudRate()
{
    return wxAtoi(GetStringSelection());
}