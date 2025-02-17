﻿/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/timer.h>
#include <wx/wx.h>

#include "Common/wxTools.h"

wxDECLARE_EVENT(wxtEVT_SETTINGS_INPUT_WRITE, wxCommandEvent);
wxDECLARE_EVENT(wxtEVT_SETTINGS_INPUT_FORMAT, wxCommandEvent);

struct PageSettingsInputParameterKeys
{
    std::string cycleInterval = {"cycleInterval"};
    std::string textFormat = {"textFormat"};
    std::string popup = {"popup"};
};

class PageSettingsInputPopup;
class TextFormatComboBox;
class PageSettingsInput : public wxStaticBoxSizer
{
public:
    PageSettingsInput(wxWindow *parent);

    void Load(const wxtJson &parameters);
    wxtJson Save() const;
    int GetInterval() const;
    int GetTextFormat() const;
    void DoStopTimer();
    PageSettingsInputPopup *GetPopup();

private:
    wxButton *m_settings{nullptr};
    wxButton *m_send{nullptr};
    wxComboBox *m_interval{nullptr};
    TextFormatComboBox *m_format{nullptr};
    PageSettingsInputPopup *m_popup{nullptr};
    wxWindow *m_parent{nullptr};
    wxTimer m_timer;

private:
    void OnSendButtonClicked(wxCommandEvent &);
    void OnInputFormatChangehd(wxCommandEvent &);
    void OnIntervalChanged(wxCommandEvent &);
    void OnTimer(wxTimerEvent &);

    wxComboBox *InitCycleIntervalComboBox();
};
