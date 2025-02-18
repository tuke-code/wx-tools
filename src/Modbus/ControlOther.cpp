/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlOther.h"

#include <wx/button.h>

namespace Modbus {

ControlOther::ControlOther(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Other Settings"))
{
    wxGridBagSizer *sizer = new wxGridBagSizer(5, 5);
    Add(sizer, 0, wxEXPAND | wxALL);

    auto clearBtn = new wxButton(parent, wxID_ANY, _("Clear"));
    sizer->Add(clearBtn, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    auto newBtn = new wxButton(parent, wxID_ANY, _("New"));
    sizer->Add(newBtn, wxGBPosition(0, 1), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
}

ControlOther::~ControlOther() {}

} // namespace Modbus
