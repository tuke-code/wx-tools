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

class ControlPanelOutputPopup;
class TextFormatComboBox;
class ControlPanelOutput : public wxStaticBoxSizer
{
public:
    ControlPanelOutput(wxWindow *parent);
    TextFormat GetTextFormat() const;
    bool GetShowDate() const;
    bool GetShowTime() const;
    bool GetShowMs() const;
    bool GetShowRx() const;
    bool GetShowTx() const;
    bool GetShowFlag() const;

    wxToolsSignal<bool> &GetWrapSignal();
    wxToolsSignal<> &GetClearSignal();

private:
    TextFormatComboBox *m_textFormatComboBox;
    wxCheckBox *m_showDate;
    wxCheckBox *m_showTime;
    wxCheckBox *m_showMs;
    wxCheckBox *m_showRx;
    wxCheckBox *m_showTx;
    wxCheckBox *m_showFlag;
    ControlPanelOutputPopup *m_popup;

    wxToolsSignal<> m_clearSignal;
};
