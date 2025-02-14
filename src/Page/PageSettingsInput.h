/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

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
    struct Context
    {
        wxButton *settings{nullptr};
        wxButton *send{nullptr};
        wxComboBox *cycleInterval{nullptr};
        TextFormatComboBox *format{nullptr};
        PageSettingsInputPopup *popup{nullptr};
    };

public:
    PageSettingsInput(wxWindow *parent);

    void Load(const wxtJson &parameters);
    wxtJson Save() const;
    Context GetContext();
    int GetInterval() const;
    void SetCycleIntervalSelection(int selection) const;
    int GetTextFormat() const;

private:
    Context m_context;

private:
    //void OnSendButtonClicked(wxCommandEvent &event);
    //void OnTextFormat(wxCommandEvent &event);

    wxComboBox *InitCycleIntervalComboBox();
};
