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

class OutputPopup;
class TextFormatComboBox;
class OutputControlBox : public wxStaticBoxSizer
{
public:
    OutputControlBox(wxWindow *parent);
    TextFormat GetTextFormat() const;
    bool GetShowDate() const;
    bool GetShowTime() const;
    bool GetShowMs() const;
    bool GetShowRx() const;
    bool GetShowTx() const;
    bool GetShowFlag() const;

    sigslot::signal<bool> &GetWrapSignal();
    sigslot::signal<> &GetClearSignal();

private:
    TextFormatComboBox *m_textFormatComboBox;
    wxCheckBox *m_showDate;
    wxCheckBox *m_showTime;
    wxCheckBox *m_showMs;
    wxCheckBox *m_showRx;
    wxCheckBox *m_showTx;
    wxCheckBox *m_showFlag;
    OutputPopup *m_popup;

    sigslot::signal<> m_clearSignal;
};
