/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlLink.h"

#include <wx/button.h>

namespace Modbus {

ControlLink::ControlLink(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Link settings"))
{
    auto sizer = new wxGridBagSizer(4, 4);
    auto text = new wxStaticText(parent, wxID_ANY, _("Link type"));
    sizer->Add(text, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    auto cb = new wxComboBox(parent,
                             wxID_ANY,
                             wxEmptyString,
                             wxDefaultPosition,
                             wxDefaultSize,
                             0,
                             nullptr,
                             wxCB_READONLY);
    cb->Append("Rtu");
    cb->Append("Tcp");
    cb->SetSelection(0);
    sizer->Add(cb, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->AddGrowableCol(1);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    AddSpacer(2);

    auto btnSizer = new wxBoxSizer(wxHORIZONTAL);
    auto btn = new wxButton(parent, wxID_ANY, _("Close"));
    btnSizer->Add(btn, 1, wxEXPAND | wxALL, 0);
    btn = new wxButton(parent, wxID_ANY, _("Open"));
    btnSizer->Add(btn, 1, wxEXPAND | wxALL, 0);
    Add(btnSizer, 0, wxEXPAND, 0);
}

ControlLink::~ControlLink() {}

} // namespace Modbus
