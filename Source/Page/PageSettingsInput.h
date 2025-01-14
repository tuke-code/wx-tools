/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <sigslot/signal.hpp>
#include <wx/wx.h>

#include "Common/wxTools.h"

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
    void SetCycleIntervalComboBoxSelection(int selection);
    TextFormat GetTextFormat() const;

    wxToolsSignal<TextFormat> invokeWriteSignal;
    wxToolsSignal<int> invokeStartTimerSignal;
    wxToolsSignal<TextFormat> textFormatChangedSignal;

private:
    wxButton *m_settingsButton{nullptr};
    wxButton *m_sendButton{nullptr};
    wxComboBox *m_cycleIntervalComboBox{nullptr};
    TextFormatComboBox *m_formatComboBox{nullptr};
    PageSettingsInputPopup *m_popup{nullptr};

private:
    void OnSendButtonClicked(wxCommandEvent &event);
    void OnTextFormat(wxCommandEvent &event);

    wxComboBox *InitCycleIntervalComboBox();
};
