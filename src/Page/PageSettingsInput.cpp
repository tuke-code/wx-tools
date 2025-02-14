/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageSettingsInput.h"

#include <wx/gbsizer.h>
#include <wx/wx.h>

#include "PageSettingsInputPopup.h"
#include "Utilities/TextFormatComboBox.h"

PageSettingsInput::PageSettingsInput(wxWindow* parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Input Settings"))
    , m_context{nullptr}
{
    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, _("Cycle"));
    m_context.cycleInterval = InitCycleIntervalComboBox();
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, _("Format"));
    m_context.format = new TextFormatComboBox(GetStaticBox());
    //m_context.format->Bind(wxEVT_COMBOBOX_DROPDOWN, &PageSettingsInput::OnTextFormat, this);
    m_context.settings = new wxButton(GetStaticBox(), wxID_ANY, _("Settings"));
    m_context.send = new wxButton(GetStaticBox(), wxID_ANY, _("Send"));
    m_context.popup = new PageSettingsInputPopup(m_context.settings);
    //m_context.send->Bind(wxEVT_BUTTON, &PageSettingsInput::OnSendButtonClicked, this);

    auto* sizer = new wxGridBagSizer(4, 4);
    sizer->Add(cycleText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_context.cycleInterval, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(formatText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_context.format, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->AddGrowableCol(1);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    AddSpacer(4);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(m_context.settings, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_context.send, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND | wxALL, 0);
}

void PageSettingsInput::Load(const wxtJson& parameters)
{
    PageSettingsInputParameterKeys keys;
    // clang-format off
    int cycleInterval = wxtGetJsonObjValue<int>(parameters, keys.cycleInterval, -1);
    int textFormat = wxtGetJsonObjValue<int>(parameters, keys.textFormat, static_cast<int>(TextFormat::Hex));
    wxtJson popup = wxtGetJsonObjValue<wxtJson>(parameters, keys.popup, wxtJson::object());
    // clang-format on

    SetComboBoxSectionByIntClientData(m_context.cycleInterval, cycleInterval);
    SetComboBoxSectionByIntClientData(m_context.format, textFormat);
    m_context.popup->Load(popup);
}

wxtJson PageSettingsInput::Save() const
{
    PageSettingsInputParameterKeys keys;
    wxtJson parameters;

    int selection = m_context.cycleInterval->GetSelection();
    void* clientData = m_context.cycleInterval->GetClientData(selection);
    if (clientData) {
        int cycleInterval = *static_cast<int*>(clientData);
        parameters[keys.cycleInterval] = cycleInterval;
    }

    selection = m_context.format->GetSelection();
    clientData = m_context.format->GetClientData(selection);
    if (clientData) {
        int textFormat = *static_cast<int*>(clientData);
        parameters[keys.textFormat] = textFormat;
    }

    parameters[keys.popup] = m_context.popup->Save();
    return parameters;
}

void PageSettingsInput::SetCycleIntervalSelection(int selection) const
{
    if (selection >= 0 && selection < m_context.cycleInterval->GetCount()) {
        m_context.cycleInterval->SetSelection(selection);
    }
}

int PageSettingsInput::GetTextFormat() const
{
    int selection = m_context.format->GetSelection();
    void* clientData = m_context.format->GetClientData(selection);
    if (clientData) {
        return *static_cast<int*>(clientData);
    }

    return static_cast<int>(TextFormat::Hex);
}

PageSettingsInput::Context PageSettingsInput::GetContext()
{
    return m_context;
}

int PageSettingsInput::GetInterval() const
{
    int selection = m_context.cycleInterval->GetSelection();
    void* clientData = m_context.cycleInterval->GetClientData(selection);
    if (clientData) {
        return *static_cast<int*>(clientData);
    }

    return -1;
}

wxComboBox* PageSettingsInput::InitCycleIntervalComboBox()
{
    auto cb = new wxComboBox(GetStaticBox(),
                             wxID_ANY,
                             wxEmptyString,
                             wxDefaultPosition,
                             wxDefaultSize,
                             0,
                             nullptr,
                             wxCB_READONLY);

    cb->Append(_("Disabled"), new int(-1));
    std::vector<int> items;
    for (int i = 10; i <= 100; i += 10) {
        items.push_back(i);
    }
    for (int i = 100; i <= 1000; i += 100) {
        items.push_back(i);
    }
    for (int i = 2000; i <= 10000; i += 1000) {
        items.push_back(i);
    }
    for (auto it = items.begin(); it != items.end(); ++it) {
        cb->Append(wxString::Format("%d ms", *it), new int(*it));
    }

    cb->SetSelection(0);
    return cb;
}
