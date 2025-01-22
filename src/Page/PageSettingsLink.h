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

class PageSettingsLinkPopup;
class LinkUi;
class PageSettingsLink : public wxStaticBoxSizer
{
public:
    PageSettingsLink(LinkType type, wxWindow *parent);

    wxtSignal<> invokeOpenSignal;

    void Load(const wxtJson &parameters);
    wxtJson Save() const;

    LinkUi *GetLinkUi() const;
    void SetOpenButtonLabel(const wxString &label);
    PageSettingsLinkPopup *GetPopup() const;

private:
    LinkUi *m_linkUi;
    wxButton *m_openButton;
    PageSettingsLinkPopup *m_popup;

private:
    LinkUi *CreateLinkUi(LinkType type, wxWindow *parent);
};
