﻿/***************************************************************************************************
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
    : wxStaticBoxSizer(wxVERTICAL, parent, _("Link Settings"))
    , m_parent(parent)
    , m_linkUi(nullptr)
    , m_popup(nullptr)
{
    m_linkUi = CreateLinkUi(type, GetStaticBox());
    Add(m_linkUi, 0, wxEXPAND, 0);

    AddSpacer(4);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, _("Settings"));
    m_popup = new PageSettingsLinkPopup(settingsButton, parent);
    m_openButton = new wxButton(GetStaticBox(), wxID_ANY, _("Open"));

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_openButton, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND, 0);

    m_openButton->Bind(wxEVT_BUTTON, &PageSettingsLink::OnOpen, this);
}

void PageSettingsLink::DoLoad(const wxtJson &parameters)
{
    m_linkUi->DoLoad(parameters);
}

wxtJson PageSettingsLink::DoSave() const
{
    return m_linkUi->DoSave();
}

wxButton *PageSettingsLink::GetOpenButton() const
{
    return m_openButton;
}

LinkUi *PageSettingsLink::GetLinkUi() const
{
    return m_linkUi;
}

PageSettingsLinkPopup *PageSettingsLink::GetPopup() const
{
    return m_popup;
}

LinkUi *PageSettingsLink::CreateLinkUi(LinkType type, wxWindow *parent)
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

void PageSettingsLink::OnOpen(wxCommandEvent &)
{
    wxPostEvent(m_parent, wxCommandEvent(wxtEVT_SETTINGS_LINK_OPEN));
}
