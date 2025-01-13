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

#include "Common/wxTools.h"

class ControlPanelLinkPopup;
class LinksController;
class ControlPanelLink : public wxStaticBoxSizer
{
public:
    ControlPanelLink(LinkType type, wxWindow *parent);
    LinksController *GetController() const;
    wxToolsSignal<> &GetInvokeOpenSignal();
    void SetOpenButtonLabel(const wxString &label);

private:
    LinksController *m_controller;
    wxButton *m_openButton;
    ControlPanelLinkPopup *m_popup;

    wxToolsSignal<> m_invokeOpenSignal;

private:
    void OnOpen(wxCommandEvent &event);
};
