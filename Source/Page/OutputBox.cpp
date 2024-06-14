/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "OutputBox.h"

OutputBox::OutputBox(wxWindow* parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Output"))
{
    auto textCtrl = new wxTextCtrl(parent,
                                   wxID_ANY,
                                   wxEmptyString,
                                   wxDefaultPosition,
                                   wxDefaultSize,
                                   wxTE_MULTILINE);

    Add(textCtrl, 1, wxEXPAND | wxALL, 0);
}