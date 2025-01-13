/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "IOPanel.h"

#include "IOPanelInput.h"
#include "IOPanelOutput.h"

IOPanel::IOPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);

    m_outputBox = new IOPanelOutput(this);
    sizer->Add(m_outputBox, 1, wxEXPAND | wxALL, 0);

    m_inputBox = new IOPanelInput(this);
    sizer->Add(m_inputBox, 0, wxEXPAND | wxALL, 0);
}

IOPanelInput *IOPanel::GetInputBox() const
{
    return m_inputBox;
}

IOPanelOutput *IOPanel::GetOutputBox() const
{
    return m_outputBox;
}
