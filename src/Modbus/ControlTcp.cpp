/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlTcp.h"

#include <wx/spinctrl.h>

#include "Utilities/IpComboBox.h"

namespace Modbus {

ControlTcp::ControlTcp(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("TCP Settings"))
{
    auto sizer = new wxGridBagSizer(4, 4);
    auto label = new wxStaticText(parent, wxID_ANY, _("IP"));
    sizer->Add(label, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto cb = new IpComboBox(parent);
    sizer->Add(cb, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    label = new wxStaticText(parent, wxID_ANY, _("Port"));
    sizer->Add(label, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto sp = new wxSpinCtrl(parent, wxID_ANY);
    sizer->Add(sp, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sp->SetRange(1, 65535);
    sp->SetValue(513);

    sizer->AddGrowableCol(1);
    Add(sizer, 1, wxEXPAND | wxALL, 0);
}

ControlTcp::~ControlTcp() {}

} // namespace Modbus
