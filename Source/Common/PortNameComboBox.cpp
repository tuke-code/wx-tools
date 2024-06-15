/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PortNameComboBox.h"

PortNameComboBox::PortNameComboBox(wxWindow* parent)
    : ComboBox(parent)
{
    Append(wxT("COM1"));
    Append(wxT("COM2"));
    Append(wxT("COM3"));
    Append(wxT("COM4"));
    Append(wxT("COM5"));
    Append(wxT("COM6"));

    SetSelection(0);
}