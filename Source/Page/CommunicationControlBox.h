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

class CommunicationPopup;
class CommunicationController;
class CommunicationControlBox : public wxStaticBoxSizer
{
public:
    CommunicationControlBox(CommunicationType type, wxWindow *parent);
    CommunicationController *GetController() const;
    eToolsSignal<> &GetInvokeOpenSignal();
    void SetOpenButtonLabel(const wxString &label);

private:
    CommunicationController *m_controller;
    wxButton *m_openButton;
    CommunicationPopup *m_popup;

    eToolsSignal<> m_invokeOpenSignal;

private:
    void OnOpen(wxCommandEvent &event);
};
