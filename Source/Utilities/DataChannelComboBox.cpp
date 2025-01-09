/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "DataChannelComboBox.h"

#include <websocketpp/client.hpp>

DataChannelComboBox::DataChannelComboBox(wxWindow* parent)
    : wxComboBox(parent,
                 wxID_ANY,
                 wxEmptyString,
                 wxDefaultPosition,
                 wxDefaultSize,
                 0,
                 nullptr,
                 wxCB_READONLY)
{
    m_dataChannels[0] = (wxString("Text channel"));
    m_dataChannels[1] = (wxString("Binary channel"));
}

int DataChannelComboBox::GetDataChannel() const
{
    wxString txt = GetValue();
    for (auto& pair : m_dataChannels) {
        if (pair.second == txt) {
            return pair.first;
        }
    }

    return 0;
}

void DataChannelComboBox::SetDataChannel(int dataChannel)
{
    wxString txt = m_dataChannels[dataChannel];
    int selection = FindString(txt);
    if (selection != wxNOT_FOUND) {
        SetSelection(selection);
    }
}
