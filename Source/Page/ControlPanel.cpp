/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlBoxes.h"

#include <wx/stattext.h>

#include "InputControlBox.h"
#include "LinkControlBox.h"
#include "OutputControlBox.h"

ControlBoxes::ControlBoxes(LinkType type, wxWindow *parent)
    : wxBoxSizer(wxVERTICAL)
    , m_inputControlBox(nullptr)
    , m_outputControlBox(nullptr)
    , m_communicationControlBox(nullptr)
{
    m_communicationControlBox = new LinkControlBox(type, parent);
    Add(m_communicationControlBox, 0, wxEXPAND | wxALL);

    m_outputControlBox = new OutputControlBox(parent);
    Add(m_outputControlBox, 0, wxEXPAND | wxALL);

    Add(new wxStaticText(parent, wxID_ANY, ""), 1, wxEXPAND);

    m_inputControlBox = new InputControlBox(parent);
    Add(m_inputControlBox, 0, wxEXPAND | wxALL);
}

InputControlBox *ControlBoxes::GetInputControlBox() const
{
    return m_inputControlBox;
}

OutputControlBox *ControlBoxes::GetOutputControlBox() const
{
    return m_outputControlBox;
}

LinkControlBox *ControlBoxes::GetCommunicationControlBox() const
{
    return m_communicationControlBox;
}
