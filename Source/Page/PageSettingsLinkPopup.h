/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/spinctrl.h>
#include <wx/wx.h>

#include "Common/wxTools.h"
#include "Utilities/BaseSettingsPopup.h"

struct PageSettingsLinkPopupParameterKeys
{
    std::string autoReconnect = "autoReconnect";
};

class PageSettingsLinkPopup : public BaseSettingsPopup
{
public:
    PageSettingsLinkPopup(wxButton *controlButton);

    wxToolsSignal<> emitRefreshSignal;

    void Load(const wxToolsJson &parameters);
    wxToolsJson Save() const;

private:
    wxButton *m_refresh;
    wxCheckBox *m_autoReconnect;
};
