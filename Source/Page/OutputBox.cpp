/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "OutputBox.h"

OutputBox::OutputBox(wxWindow* parent, wxWindowID id)
    : wxStaticBox(parent, id, _("Output"))
{
    auto sizer = new wxBoxSizer(wxVERTICAL);
    auto textCtrl = new wxTextCtrl(this,
                                   wxID_ANY,
                                   wxEmptyString,
                                   wxDefaultPosition,
                                   wxDefaultSize,
                                   wxTE_MULTILINE);
    textCtrl->AppendText("Hello, World!");
    textCtrl->AppendText("Hello");

    sizer->Add(textCtrl, 2, wxEXPAND | wxALL, 0);
    SetSizerAndFit(sizer);
}