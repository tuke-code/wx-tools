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
    : ComboBox(parent)
{
    Append("1");
    Append("1.5");
    Append("2");
    SetSelection(0);
}