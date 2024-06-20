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

class TextFormatComboBox;
class InputControlBox : public wxStaticBoxSizer
{
public:
    InputControlBox(wxWindow *parent);
    void SetCycleIntervalComboBoxSelection(int selection);
    TextFormat GetTextFormat() const;

    sigslot::signal<TextFormat> &GetInvokeWriteSignal();
    sigslot::signal<int> &GetInvokeStartTimerSignal();

private:
    wxButton *m_sendButton;
    wxComboBox *m_cycleIntervalComboBox;
    TextFormatComboBox *m_formatComboBox;

    sigslot::signal<TextFormat> m_invokeWriteSignal;
    sigslot::signal<int> m_invokeStartTimerSignal;
};
