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
    , m_linkSettings(nullptr)
    , m_outputSettings(nullptr)
    , m_inputSettings(nullptr)
{
    m_linkSettings = new PageSettingsLink(type, parent);
    Add(m_linkSettings, 0, wxEXPAND | wxALL);

    m_outputSettings = new PageSettingsOutput(parent);
    Add(m_outputSettings, 0, wxEXPAND | wxALL);

    Add(new wxStaticText(parent, wxID_ANY, ""), 1, wxEXPAND);

    m_inputSettings = new PageSettingsInput(parent);
    Add(m_inputSettings, 0, wxEXPAND | wxALL);
}

void PageSettings::Load(const wxToolsJson &parameters)
{
    PageSettingsParameterKeys keys;
    m_linkSettings->Load(parameters[keys.linkSettings].template get<wxToolsJson>());
    m_outputSettings->Load(parameters[keys.outputSettings].template get<wxToolsJson>());
    m_inputSettings->Load(parameters[keys.inputSettings].template get<wxToolsJson>());
}

wxToolsJson PageSettings::Save() const
{
    wxToolsJson parameters;
    PageSettingsParameterKeys keys;
    parameters[keys.linkSettings] = m_linkSettings->Save();
    parameters[keys.outputSettings] = m_outputSettings->Save();
    parameters[keys.inputSettings] = m_inputSettings->Save();
    return parameters;
}

PageSettingsLink *PageSettings::GetLinkSettings() const
{
    return m_linkSettings;
}

PageSettingsOutput *PageSettings::GetOutputSettings() const
{
    return m_outputSettings;
}

PageSettingsInput *PageSettings::GetInputSettings() const
{
    return m_inputSettings;
}
