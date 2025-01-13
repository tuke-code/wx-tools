/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageSettingsLink.h"

#include "LinksUi/LinkUi.h"
#include "LinksUi/SerialPortUi.h"
#include "LinksUi/TCPClientUi.h"
#include "LinksUi/TCPServerUi.h"
#include "LinksUi/UDPClientUi.h"
#include "LinksUi/UDPServerUi.h"
#include "LinksUi/WSClientUi.h"
#include "LinksUi/WSServerUi.h"
#include "PageSettingsLinkPopup.h"

PageSettingsLink::PageSettingsLink(LinkType type, wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Link Settings"))
    , m_controller(nullptr)
    , m_popup(nullptr)
{
    m_controller = CreateLinkController(type, GetStaticBox());
    Add(m_controller, 0, wxEXPAND, 0);

    AddSpacer(4);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    m_popup = new PageSettingsLinkPopup(settingsButton);

    m_openButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Open"));
    m_openButton->Bind(wxEVT_BUTTON, &PageSettingsLink::OnOpen, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_openButton, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND, 0);
}

LinkUi *PageSettingsLink::GetController() const
{
    return m_controller;
}

wxToolsSignal<> &PageSettingsLink::GetInvokeOpenSignal()
{
    return m_invokeOpenSignal;
}

void PageSettingsLink::SetOpenButtonLabel(const wxString &label)
{
    m_openButton->SetLabel(label);
}

void PageSettingsLink::OnOpen(wxCommandEvent &event)
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

LinkUi *PageSettingsLink::CreateLinkController(LinkType type, wxWindow *parent)
{
    if (type == LinkType::SerialPort) {
        return new SerialPortUi(parent);
    } else if (type == LinkType::UDPClient) {
        return new UDPClientUi(parent);
    } else if (type == LinkType::UDPServer) {
        return new UDPServerUi(parent);
    } else if (type == LinkType::TCPClient) {
        return new TCPClientUi(parent);
    } else if (type == LinkType::TCPServer) {
        return new TCPServerUi(parent);
    } else if (type == LinkType::WSClient) {
        return new WSClientUi(parent);
    } else if (type == LinkType::WSServer) {
        return new WSServerUi(parent);
    }

    return nullptr;
}
