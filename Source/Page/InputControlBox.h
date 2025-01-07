/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <sigslot/signal.hpp>
#include <wx/wx.h>

#include "Common/eTools.h"

class InputPopup;
class TextFormatComboBox;
class InputControlBox : public wxStaticBoxSizer
{
public:
    InputControlBox(wxWindow *parent);
    void SetCycleIntervalComboBoxSelection(int selection);
    TextFormat GetTextFormat() const;

    wxToolsSignal<TextFormat> &GetInvokeWriteSignal();
    wxToolsSignal<int> &GetInvokeStartTimerSignal();
    wxToolsSignal<TextFormat> &GetTextFormatChangedSignal();

private:
    wxButton *m_settingsButton;
    wxButton *m_sendButton;
    wxComboBox *m_cycleIntervalComboBox;
    TextFormatComboBox *m_formatComboBox;
    InputPopup *m_popup;

private:
    wxToolsSignal<TextFormat> m_invokeWriteSignal;
    wxToolsSignal<int> m_invokeStartTimerSignal;
    wxToolsSignal<TextFormat> m_textFormatChangedSignal;

    void OnSendButtonClicked(wxCommandEvent &event);
    void OnTextFormat(wxCommandEvent &event);

    wxComboBox *InitCycleIntervalComboBox();
};
