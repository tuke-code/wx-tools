/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageSettingsInputPopup.h"

#include <wx/gbsizer.h>
#include <wx/popupwin.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>

#include "Utilities/AdditionComboBox.h"
#include "Utilities/CRCTypeComboBox.h"
#include "Utilities/ESCComboBox.h"

PageSettingsInputPopup::PageSettingsInputPopup(wxButton *controlButton)
    : BaseSettingsPopup(controlButton, false)
{
    auto panel = new wxPanel(this);
    auto prefixLabel = new wxStaticText(panel, wxID_ANY, wxT("Prefix"));
    m_prefixComboBox = new AdditionComboBox(panel);
    auto suffixLabel = new wxStaticText(panel, wxID_ANY, wxT("Suffix"));
    m_suffixComboBox = new AdditionComboBox(panel);
    auto escLabel = new wxStaticText(panel, wxID_ANY, wxT("ESC"));
    m_escComboBox = new ESCComboBox(panel);

    auto startIndexLabel = new wxStaticText(panel, wxID_ANY, wxT("Start Index"));
    m_startIndexSpinCtrl = new wxSpinCtrl(panel, wxID_ANY);
    auto endIndexLabel = new wxStaticText(panel, wxID_ANY, wxT("End Index"));
    m_endIndexSpinCtrl = new wxSpinCtrl(panel, wxID_ANY);
    auto algorithmLabel = new wxStaticText(panel, wxID_ANY, wxT("Algorithm"));
    m_algorithmComboBox = new CRCTypeComboBox(panel);
    m_addCrcCheckBox = new wxCheckBox(panel, wxID_ANY, wxT("Add CRC"));
    m_bigEndianCheckBox = new wxCheckBox(panel, wxID_ANY, wxT("Big Endian"));

    // clang-format off
    auto sizer = new wxGridBagSizer(4, 4);
    sizer->Add(prefixLabel, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_prefixComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(suffixLabel, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_suffixComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(escLabel, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_escComboBox, wxGBPosition(2, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    auto line = new wxStaticLine(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    sizer->Add(line, wxGBPosition(3, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);

    sizer->Add(startIndexLabel, wxGBPosition(4, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_startIndexSpinCtrl, wxGBPosition(4, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(endIndexLabel, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_endIndexSpinCtrl, wxGBPosition(5, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(algorithmLabel, wxGBPosition(6, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_algorithmComboBox, wxGBPosition(6, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    // clang-format on

    auto hSizer = new wxBoxSizer(wxHORIZONTAL);
    hSizer->Add(m_addCrcCheckBox, 1, wxEXPAND | wxALL, 0);
    hSizer->Add(m_bigEndianCheckBox, 1, wxEXPAND | wxALL, 0);
    sizer->Add(hSizer, wxGBPosition(7, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);

    sizer->AddGrowableCol(1);
    panel->SetMinSize(wxSize(152, -1));
    panel->SetSizerAndFit(sizer);

    int padding = 8;
    auto panelSizer = new wxBoxSizer(wxVERTICAL);
    panelSizer->Add(panel, 1, wxEXPAND | wxALL, padding);
    SetSizerAndFit(panelSizer);

    m_prefixComboBox->Bind(wxEVT_COMBOBOX, &PageSettingsInputPopup::OnParametersChanged, this);
    m_suffixComboBox->Bind(wxEVT_COMBOBOX, &PageSettingsInputPopup::OnParametersChanged, this);
    m_escComboBox->Bind(wxEVT_COMBOBOX, &PageSettingsInputPopup::OnParametersChanged, this);
    m_startIndexSpinCtrl->Bind(wxEVT_SPINCTRL, &PageSettingsInputPopup::OnParametersChanged, this);
    m_endIndexSpinCtrl->Bind(wxEVT_SPINCTRL, &PageSettingsInputPopup::OnParametersChanged, this);
    m_algorithmComboBox->Bind(wxEVT_COMBOBOX, &PageSettingsInputPopup::OnParametersChanged, this);
    m_addCrcCheckBox->Bind(wxEVT_CHECKBOX, &PageSettingsInputPopup::OnParametersChanged, this);
    m_bigEndianCheckBox->Bind(wxEVT_CHECKBOX, &PageSettingsInputPopup::OnParametersChanged, this);
}

void PageSettingsInputPopup::Load(const wxtJson &json)
{
    PageSettingsInputPopupParameterKeys keys;
    int prefix = json[keys.prefix].get<int>();
    int suffix = json[keys.suffix].get<int>();
    int escIndex = json[keys.escIndex].get<int>();
    int startIndex = json[keys.startIndex].get<int>();
    int endIndex = json[keys.endIndex].get<int>();
    int algorithm = json[keys.algorithm].get<int>();
    bool addCrc = json[keys.addCrc].get<bool>();
    bool bigEndian = json[keys.bigEndian].get<bool>();

    wxToolsSetComboBoxSectionByIntClientData(m_prefixComboBox, prefix);
    wxToolsSetComboBoxSectionByIntClientData(m_suffixComboBox, suffix);
    wxToolsSetComboBoxSectionByIntClientData(m_escComboBox, escIndex);
    m_startIndexSpinCtrl->SetValue(startIndex);
    m_endIndexSpinCtrl->SetValue(endIndex);
    wxToolsSetComboBoxSectionByIntClientData(m_algorithmComboBox, algorithm);
    m_addCrcCheckBox->SetValue(addCrc);
    m_bigEndianCheckBox->SetValue(bigEndian);
}

wxtJson PageSettingsInputPopup::Save() const
{
    PageSettingsInputPopupParameterKeys keys;
    wxtJson json;

    int prefixSelection = m_prefixComboBox->GetSelection();
    int suffixSelection = m_suffixComboBox->GetSelection();
    int escSelection = m_escComboBox->GetSelection();
    int algorithmSelection = m_algorithmComboBox->GetSelection();

    // clang-format off
    json[keys.prefix] = *static_cast<int *>(m_prefixComboBox->GetClientData(prefixSelection));
    json[keys.suffix] = *static_cast<int *>(m_suffixComboBox->GetClientData(suffixSelection));
    json[keys.escIndex] = *static_cast<int *>(m_escComboBox->GetClientData(escSelection));
    json[keys.startIndex] = m_startIndexSpinCtrl->GetValue();
    json[keys.endIndex] = m_endIndexSpinCtrl->GetValue();
    json[keys.algorithm] = *static_cast<int *>(m_algorithmComboBox->GetClientData(algorithmSelection));
    json[keys.addCrc] = m_addCrcCheckBox->GetValue();
    json[keys.bigEndian] = m_bigEndianCheckBox->GetValue();
    // clang-format on

    return json;
}

void PageSettingsInputPopup::OnParametersChanged(wxCommandEvent &event)
{
    wxUnusedVar(event);
    parametersChangedSignal();
}
