/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageSettings.h"

#include <wx/stattext.h>

#include "PageSettingsLink.h"
#include "PageSettingsInput.h"
#include "PageSettingsOutput.h"

PageSettings::PageSettings(LinkType type, wxWindow *parent)
    : wxBoxSizer(wxVERTICAL)
    , m_inputControlBox(nullptr)
    , m_outputControlBox(nullptr)
    , m_communicationControlBox(nullptr)
{
    m_communicationControlBox = new PageSettingsLink(type, parent);
    Add(m_communicationControlBox, 0, wxEXPAND | wxALL);

    m_outputControlBox = new PageSettingsOutput(parent);
    Add(m_outputControlBox, 0, wxEXPAND | wxALL);

    Add(new wxStaticText(parent, wxID_ANY, ""), 1, wxEXPAND);

    m_inputControlBox = new PageSettingsInput(parent);
    Add(m_inputControlBox, 0, wxEXPAND | wxALL);
}

PageSettingsInput *PageSettings::GetInputControlBox() const
{
    return m_inputControlBox;
}

PageSettingsOutput *PageSettings::GetOutputControlBox() const
{
    return m_outputControlBox;
}

PageSettingsLink *PageSettings::GetCommunicationControlBox() const
{
    return m_communicationControlBox;
}
