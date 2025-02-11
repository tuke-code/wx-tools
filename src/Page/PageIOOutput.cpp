/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageIOOutput.h"

PageIOOutput::PageIOOutput(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Output"))
    , m_textCtrl(nullptr)
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

void PageIOOutput::AppendText(const wxString &text, bool newLine)
{
    if (newLine) {
        m_textCtrl->AppendText(text + "\n");
    } else {
        m_textCtrl->AppendText(text);
    }
}

void PageIOOutput::SetWrap(bool wrap)
{
    long wrapMode = wrap ? wxTE_CHARWRAP : wxTE_DONTWRAP;
    long oldFlag = m_textCtrl->GetWindowStyleFlag();
    long newFlag = (oldFlag & (~wxTE_CHARWRAP) & (~wxTE_DONTWRAP)) | wrapMode;
    m_textCtrl->SetWindowStyleFlag(newFlag);
}

void PageIOOutput::Clear()
{
    m_textCtrl->Clear();
}
