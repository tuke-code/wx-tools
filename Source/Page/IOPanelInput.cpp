/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "IOPanelInput.h"

#include "Utilities/LineEdit.h"

IOPanelInput::IOPanelInput(wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Input"))
{
    m_lineEdit = new LineEdit(parent);
    Add(m_lineEdit, 1, wxEXPAND | wxALL, 0);
}

wxString IOPanelInput::GetInputText() const
{
    return m_lineEdit->GetValue();
}

void IOPanelInput::SetTextFormat(TextFormat format)
{
    m_lineEdit->Clear();
    m_lineEdit->SetTextFormat(format);
}

wxToolsConstBuffer IOPanelInput::GetInputBuffer() const
{
    return m_lineEdit->GetBuffer();
}
