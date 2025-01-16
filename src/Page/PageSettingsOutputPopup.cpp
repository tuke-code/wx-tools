/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageSettingsOutputPopup.h"

#include <wx/gbsizer.h>

PageSettingsOutputPopup::PageSettingsOutputPopup(wxButton *controlButton)
    : BaseSettingsPopup(controlButton)
    , m_filterTextCtrl(nullptr)
    , m_highlightLabelsTextCtrl(nullptr)
{
    auto panel = new wxPanel(this);

    auto filterLabel = new wxStaticText(panel, wxID_ANY, wxT("Filter"));
    m_filterTextCtrl = new wxTextCtrl(panel,
                                      wxID_ANY,
                                      wxEmptyString,
                                      wxDefaultPosition,
                                      wxDefaultSize);
    auto highlightLabel = new wxStaticText(panel, wxID_ANY, wxT("Highlight"));
    m_highlightLabelsTextCtrl = new wxTextCtrl(panel,
                                               wxID_ANY,
                                               wxEmptyString,
                                               wxDefaultPosition,
                                               wxDefaultSize);

    auto panelSizer = new wxGridBagSizer(4, 4);
    panelSizer->Add(filterLabel, wxGBPosition(0, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(m_filterTextCtrl, wxGBPosition(0, 1), wxDefaultSpan, wxEXPAND);
    panelSizer->Add(highlightLabel, wxGBPosition(1, 0), wxDefaultSpan, wxALIGN_CENTER_VERTICAL);
    panelSizer->Add(m_highlightLabelsTextCtrl, wxGBPosition(1, 1), wxDefaultSpan, wxEXPAND);
    panelSizer->AddGrowableCol(1);
    panel->SetSizerAndFit(panelSizer);

    auto sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 8);
    sizer->SetMinSize(200, -1);
    SetSizerAndFit(sizer);
}

void PageSettingsOutputPopup::Load(const wxToolsJson &parameters)
{
    PageSettingsOutputPopupParameterKeys keys;
    m_filterTextCtrl->SetValue(parameters[keys.fillter].get<std::string>());
    m_highlightLabelsTextCtrl->SetValue(parameters[keys.highlightLabels].get<std::string>());
}

wxToolsJson PageSettingsOutputPopup::Save() const
{
    wxToolsJson parameters{wxToolsJson::object()};
    PageSettingsOutputPopupParameterKeys keys;
    parameters[keys.fillter] = m_filterTextCtrl->GetValue().ToStdString();
    parameters[keys.highlightLabels] = m_highlightLabelsTextCtrl->GetValue().ToStdString();
    return parameters;
}
