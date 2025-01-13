/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "IOPanelOutput.h"

IOPanelOutput::IOPanelOutput(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Output"))
{
    m_textCtrl = new wxTextCtrl(parent,
                                wxID_ANY,
                                wxEmptyString,
                                wxDefaultPosition,
                                wxDefaultSize,
                                wxTE_MULTILINE);

    Add(m_textCtrl, 1, wxEXPAND | wxALL, 0);
    m_textCtrl->SetEditable(false);
}

void IOPanelOutput::AppendText(const wxString &text)
{
    m_textCtrl->AppendText(text + "\n");
}

void IOPanelOutput::SetWrap(bool wrap)
{
    int wrapMode = wrap ? wxTE_WORDWRAP : wxTE_DONTWRAP;
    m_textCtrl->SetWindowStyleFlag(m_textCtrl->GetWindowStyleFlag() & wrapMode);
}

void IOPanelOutput::Clear()
{
    m_textCtrl->Clear();
}
