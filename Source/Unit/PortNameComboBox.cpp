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
    for (int i = 0; i < 10; i++) {
        Append(wxString::Format("COM%d", i+1));
    }

    SetSelection(9);
}