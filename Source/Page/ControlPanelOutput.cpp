/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlPanelOutput.h"

#include <wx/gbsizer.h>

#include "ControlPanelOutputPopup.h"
#include "Utilities/TextFormatComboBox.h"

ControlPanelOutput::ControlPanelOutput(wxWindow *parent)
    : wxStaticBoxSizer(wxHORIZONTAL, parent, wxT("Output Control"))
    , m_showDate(nullptr)
    , m_showTime(nullptr)
    , m_showMs(nullptr)
    , m_showRx(nullptr)
    , m_showTx(nullptr)
    , m_showFlag(nullptr)
{
    auto formatText = new wxStaticText(GetStaticBox(), wxID_ANY, wxT("Format"));
    m_textFormatComboBox = new TextFormatComboBox(GetStaticBox());
    auto optionsSizer = new wxGridBagSizer(4, 4);
    auto AddCheckBox = [=](const wxString &label, int row, int col) -> wxCheckBox * {
        auto cb = new wxCheckBox(GetStaticBox(), wxID_ANY, label);
        optionsSizer->Add(cb, wxGBPosition(row, col), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
        return cb;
    };

    m_showRx = AddCheckBox(wxT("Rx"), 0, 0);
    m_showTx = AddCheckBox(wxT("Tx"), 0, 1);
    m_showFlag = AddCheckBox(wxT("Flags"), 0, 2);
    m_showDate = AddCheckBox(wxT("Date"), 1, 0);
    m_showTime = AddCheckBox(wxT("Time"), 1, 1);
    m_showMs = AddCheckBox(wxT("MS"), 1, 2);

    m_showRx->SetValue(true);
    m_showTx->SetValue(true);
    m_showDate->SetValue(false);
    m_showTime->SetValue(true);
    m_showMs->SetValue(false);
    m_showFlag->SetValue(true);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    auto clearButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Clear"));
    auto buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonsSizer->Add(clearButton, 1, wxEXPAND | wxALL, 0);

    m_popup = new ControlPanelOutputPopup(settingsButton);

    auto *sizer = new wxGridBagSizer(4, 4);
    sizer->Add(formatText, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_textFormatComboBox, wxGBPosition(0, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(optionsSizer, wxGBPosition(1, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    sizer->Add(buttonsSizer, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    Add(sizer, 1, wxEXPAND | wxALL, 0);
    sizer->AddGrowableCol(1);

    clearButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent &event) { m_clearSignal(); });
}

TextFormat ControlPanelOutput::GetTextFormat() const
{
    return m_textFormatComboBox->GetSelectedFormat();
}

bool ControlPanelOutput::GetShowDate() const
{
    return m_showDate->GetValue();
}

bool ControlPanelOutput::GetShowTime() const
{
    return m_showTime->GetValue();
}

bool ControlPanelOutput::GetShowMs() const
{
    return m_showMs->GetValue();
}

bool ControlPanelOutput::GetShowRx() const
{
    return m_showRx->GetValue();
}

bool ControlPanelOutput::GetShowTx() const
{
    return m_showTx->GetValue();
}

bool ControlPanelOutput::GetShowFlag() const
{
    return m_showFlag->GetValue();
}

wxToolsSignal<> &ControlPanelOutput::GetClearSignal()
{
    return m_clearSignal;
}
