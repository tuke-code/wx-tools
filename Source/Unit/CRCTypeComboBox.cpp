/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CrcTypeComboBox.h"

CRCTypeComboBox::CRCTypeComboBox(wxWindow *parent)
    : wxComboBox(parent,
                 wxID_ANY,
                 eToolsNoneStr,
                 wxDefaultPosition,
                 wxDefaultSize,
                 0,
                 nullptr,
                 wxCB_READONLY)
{
    for (auto type : GetSuportedCrcTypes()) {
        Append(GetCrcName(type), new int(static_cast<int>(type)));
    }

    SetSelection(0);
}

CrcType CRCTypeComboBox::GetCrcType() const
{
    auto index = GetSelection();
    if (index == wxNOT_FOUND) {
        return CrcType::CRC_8;
    }

    return *reinterpret_cast<CrcType *>(GetClientData(index));
}

void CRCTypeComboBox::SetCrcType(CrcType type)
{
    auto index = FindString(GetCrcName(type));
    if (index != wxNOT_FOUND) {
        SetSelection(index);
    }
}