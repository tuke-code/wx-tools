/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "InputControlBox.h"

#include <wx/gbsizer.h>
#include <wx/wx.h>

#include "Unit/TextFormatComboBox.h"

InputControlBox::InputControlBox(wxWindow* parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Input Control"))
{
    auto cycleText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Cycle"));
    m_cycleIntervalComboBox = new wxComboBox(GetStaticBox(),
                                             wxID_ANY,
                                             wxEmptyString,
                                             wxDefaultPosition,
                                             wxDefaultSize,
                                             0,
                                             nullptr,
                                             wxCB_READONLY);
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Format"));
    m_formatComboBox = new TextFormatComboBox(GetStaticBox());
    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    m_sendButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Send"));

    auto* sizer = new wxGridBagSizer(4, 4);
    sizer->Add(cycleText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_cycleIntervalComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(formatText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_formatComboBox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->AddGrowableCol(1);
    Add(sizer, 0, wxEXPAND | wxALL, 0);

    AddSpacer(4);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_sendButton, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND | wxALL, 0);

    m_cycleIntervalComboBox->Append(wxT("Disabled"), new int(-1));
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
        m_cycleIntervalComboBox->Append(wxString::Format("%d ms", *it), new int(*it));
    }

    m_cycleIntervalComboBox->SetSelection(0);

    m_sendButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent& event) {
        m_invokeWriteSignal(m_formatComboBox->GetSelectedFormat());
    });

    m_cycleIntervalComboBox->Bind(wxEVT_COMBOBOX, [=](wxCommandEvent& event) {
        int selection = m_cycleIntervalComboBox->GetSelection();
        int value = *static_cast<int*>(m_cycleIntervalComboBox->GetClientData(selection));
        m_invokeStartTimerSignal(value);
    });
}

void InputControlBox::SetCycleIntervalComboBoxSelection(int selection)
{
    if (selection < 0 || selection >= m_cycleIntervalComboBox->GetCount()) {
        return;
    }

    m_cycleIntervalComboBox->SetSelection(selection);
}

TextFormat InputControlBox::GetTextFormat() const
{
    return m_formatComboBox->GetSelectedFormat();
}

sigslot::signal<TextFormat>& InputControlBox::GetInvokeWriteSignal()
{
    return m_invokeWriteSignal;
}

sigslot::signal<int>& InputControlBox::GetInvokeStartTimerSignal()
{
    return m_invokeStartTimerSignal;
}
