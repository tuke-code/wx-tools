/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageSettingsLinkPopup.h"

#include <wx/gbsizer.h>
#include <wx/statline.h>
#include <wx/wx.h>

PageSettingsLinkPopup::PageSettingsLinkPopup(wxButton *controlButton)
    : BaseSettingsPopup(controlButton)
    , m_refresh(nullptr)
    , m_autoReconnect(nullptr)
{
    wxPanel *panel = new wxPanel(this);
    m_autoReconnect = new wxCheckBox(panel, wxID_ANY, wxT("Auto Reconnect"));

    auto line1 = new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    m_refresh = new wxButton(panel, wxID_ANY, wxT("Refresh"));

    wxGridBagSizer *sizer = new wxGridBagSizer(4, 4);
    sizer->Add(m_refresh, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    sizer->Add(line1, wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    sizer->Add(m_autoReconnect, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);

    sizer->AddGrowableCol(1);
    panel->SetSizerAndFit(sizer);

    int padding = 8;
    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(panel, 1, wxEXPAND | wxALL, padding);
    panel->SetMinSize(wxSize(152, -1));
    SetSizerAndFit(panelSizer);
}

void PageSettingsLinkPopup::Load(const wxtJson &parameters)
{
    PageSettingsLinkPopupParameterKeys keys;
    bool autoReconnect = parameters[keys.autoReconnect].template get<bool>();
    m_autoReconnect->SetValue(autoReconnect);
}

wxtJson PageSettingsLinkPopup::Save() const
{
    wxtJson json = wxtJson::object();
    PageSettingsLinkPopupParameterKeys keys;

    json[keys.autoReconnect] = m_autoReconnect->GetValue();

    return json;
}
