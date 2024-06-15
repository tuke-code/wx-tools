/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "OutputControlBox.h"

#include <wx/gbsizer.h>

#include "Common/TextFormatComboBox.h"

OutputControlBox::OutputControlBox(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Output Control"))
{
    auto *sizer = new wxGridBagSizer(4, 4);
    Add(sizer, 1, wxEXPAND | wxALL, 0);

    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, _("Format:"));
    sizer->Add(formatText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    auto formatComboBox = new TextFormatComboBox(GetStaticBox());
    sizer->Add(formatComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto formatSizer = new wxGridBagSizer(4, 4);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Rx")),
                     wxGBPosition(0, 0),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Tx")),
                     wxGBPosition(0, 1),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Wrap")),
                     wxGBPosition(0, 2),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Date")),
                     wxGBPosition(1, 0),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Time")),
                     wxGBPosition(1, 1),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("MS")),
                     wxGBPosition(1, 2),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Flags")),
                     wxGBPosition(2, 0),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    formatSizer->Add(new wxCheckBox(GetStaticBox(), wxID_ANY, _("Logs")),
                     wxGBPosition(2, 1),
                     wxGBSpan(1, 1),
                     wxEXPAND | wxALL,
                     0);
    sizer->Add(formatSizer, wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);

    auto buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(new wxButton(GetStaticBox(), wxID_ANY, _("Settings")), 1, wxALL, 0);
    buttonsSizer->Add(new wxButton(GetStaticBox(), wxID_ANY, _("Clear")), 1, wxALL, 0);
    sizer->Add(buttonsSizer, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
}