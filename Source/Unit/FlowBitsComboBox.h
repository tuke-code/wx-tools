/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio/serial_port.hpp>
#include <wx/wx.h>

class FlowBitsComboBox : public wxComboBox
{
public:
    FlowBitsComboBox(wxWindow* parent = nullptr);

    asio::serial_port::flow_control::type GetFlowBits() const;
    void SetFlowBits(int flowBits);
};
