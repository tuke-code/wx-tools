/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "ControlPanelLink.h"

#include "ControlPanelLinkPopup.h"
#include "LinksUi/LinksController.h"
#include "LinksUi/LinksControllerFactory.h"

ControlPanelLink::ControlPanelLink(LinkType type, wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Link Control"))
    , m_controller(nullptr)
    , m_popup(nullptr)
{
    auto &factory = LinksControllerFactory::singleton();
    m_controller = factory.CreateLinkController(type, GetStaticBox());
    Add(m_controller, 0, wxEXPAND, 0);

    AddSpacer(4);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    m_popup = new ControlPanelLinkPopup(settingsButton);

    m_openButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Open"));
    m_openButton->Bind(wxEVT_BUTTON, &ControlPanelLink::OnOpen, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_openButton, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND, 0);
}

LinksController *ControlPanelLink::GetController() const
{
    return m_controller;
}

wxToolsSignal<> &ControlPanelLink::GetInvokeOpenSignal()
{
    return m_invokeOpenSignal;
}

void ControlPanelLink::SetOpenButtonLabel(const wxString &label)
{
    m_openButton->SetLabel(label);
}

void ControlPanelLink::OnOpen(wxCommandEvent &event)
{
#if 0
    static wxPopupTransientWindow *popup = new wxPopupTransientWindow(m_openButton, wxBORDER_SIMPLE);
    popup->SetBackgroundColour(*wxWHITE);
    popup->SetPosition(m_openButton->ClientToScreen(wxPoint(m_openButton->GetSize().GetWidth(), 0)));
    popup->Show();
#endif

    wxUnusedVar(event);
    m_invokeOpenSignal();
}
