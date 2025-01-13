/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageIO.h"

#include "PageIOInput.h"
#include "PageIOOutput.h"

PageIO::PageIO(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizerAndFit(sizer);

    m_outputBox = new PageIOOutput(this);
    sizer->Add(m_outputBox, 1, wxEXPAND | wxALL, 0);

    m_inputBox = new PageIOInput(this);
    sizer->Add(m_inputBox, 0, wxEXPAND | wxALL, 0);
}

PageIOInput *PageIO::GetInputBox() const
{
    return m_inputBox;
}

PageIOOutput *PageIO::GetOutputBox() const
{
    return m_outputBox;
}
