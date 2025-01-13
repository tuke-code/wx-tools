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
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Input Control"))
    , m_settingsButton(nullptr)
    , m_sendButton(nullptr)
{
    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Cycle"));
    m_cycleIntervalComboBox = InitCycleIntervalComboBox();
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Format"));
    m_formatComboBox = new TextFormatComboBox(GetStaticBox());
    m_formatComboBox->Bind(wxEVT_COMBOBOX, &PageSettingsInput::OnTextFormat, this);
    m_settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    m_sendButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Send"));
    m_popup = new PageSettingsInputPopup(m_settingsButton);
    m_sendButton->Bind(wxEVT_BUTTON, &PageSettingsInput::OnSendButtonClicked, this);

    auto* sizer = new wxGridBagSizer(4, 4);
    sizer->Add(cycleText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_cycleIntervalComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(formatText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_formatComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->AddGrowableCol(1);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    AddSpacer(4);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(m_settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_sendButton, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND | wxALL, 0);
}

void PageSettingsInput::SetCycleIntervalComboBoxSelection(int selection)
{
    if (selection < 0 || selection >= m_cycleIntervalComboBox->GetCount()) {
        return;
    }

    m_cycleIntervalComboBox->SetSelection(selection);
}

TextFormat PageSettingsInput::GetTextFormat() const
{
    return m_formatComboBox->GetSelectedFormat();
}

wxToolsSignal<TextFormat>& PageSettingsInput::GetInvokeWriteSignal()
{
    return m_invokeWriteSignal;
}

wxToolsSignal<int>& PageSettingsInput::GetInvokeStartTimerSignal()
{
    return m_invokeStartTimerSignal;
}

wxToolsSignal<TextFormat>& PageSettingsInput::GetTextFormatChangedSignal()
{
    return m_textFormatChangedSignal;
}

void PageSettingsInput::OnSendButtonClicked(wxCommandEvent& event)
{
    wxUnusedVar(event);
    m_invokeWriteSignal(m_formatComboBox->GetSelectedFormat());
}

void PageSettingsInput::OnTextFormat(wxCommandEvent& event)
{
    wxUnusedVar(event);
    m_textFormatChangedSignal(m_formatComboBox->GetSelectedFormat());
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

    cb->Append(wxT("Disabled"), new int(-1));
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

    cb->Bind(wxEVT_COMBOBOX, [=](wxCommandEvent& event) {
        int selection = cb->GetSelection();
        int value = *static_cast<int*>(cb->GetClientData(selection));
        m_invokeStartTimerSignal(value);
    });

    return cb;
}
