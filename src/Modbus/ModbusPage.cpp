/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ModbusPage.h"

#include "Control.h"
#include "TabPage.h"

namespace Modbus {

ModbusPage::ModbusPage(bool isMaster, wxWindow *parent)
    : wxPanel(parent)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizerAndFit(sizer);

    auto control = new Control(isMaster, this);
    sizer->Add(control, 0, wxEXPAND | wxALL, 4);

    auto tabPage = new TabPage(this);
    sizer->Add(tabPage, 1, wxEXPAND | wxALL, 4);

    Layout();
}

ModbusPage::~ModbusPage() {}

} // namespace Modbus
