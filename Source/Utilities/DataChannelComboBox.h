/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio/serial_port.hpp>
#include <map>
#include <wx/wx.h>

class DataChannelComboBox : public wxComboBox
{
public:
    DataChannelComboBox(wxWindow* parent = nullptr);
    int GetDataChannel() const;
    void SetDataChannel(int dataChannel);

private:
    std::map<int, wxString> m_dataChannels;
};
