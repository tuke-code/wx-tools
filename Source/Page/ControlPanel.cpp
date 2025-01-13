/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlPanel.h"

#include <wx/stattext.h>

#include "ControlPanelLink.h"
#include "ControlPanelInput.h"
#include "ControlPanelOutput.h"

ControlPanel::ControlPanel(LinkType type, wxWindow *parent)
    : wxBoxSizer(wxVERTICAL)
    , m_inputControlBox(nullptr)
    , m_outputControlBox(nullptr)
    , m_communicationControlBox(nullptr)
{
    m_communicationControlBox = new ControlPanelLink(type, parent);
    Add(m_communicationControlBox, 0, wxEXPAND | wxALL);

    m_outputControlBox = new ControlPanelOutput(parent);
    Add(m_outputControlBox, 0, wxEXPAND | wxALL);

    Add(new wxStaticText(parent, wxID_ANY, ""), 1, wxEXPAND);

    m_inputControlBox = new ControlPanelInput(parent);
    Add(m_inputControlBox, 0, wxEXPAND | wxALL);
}

ControlPanelInput *ControlPanel::GetInputControlBox() const
{
    return m_inputControlBox;
}

ControlPanelOutput *ControlPanel::GetOutputControlBox() const
{
    return m_outputControlBox;
}

ControlPanelLink *ControlPanel::GetCommunicationControlBox() const
{
    return m_communicationControlBox;
}
