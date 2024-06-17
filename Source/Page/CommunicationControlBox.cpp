﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationControlBox.h"

#include <wx/gbsizer.h>

#include "Communication/CommunicationController.h"
#include "Communication/CommunicationControllerFactory.h"

CommunicationControlBox::CommunicationControlBox(CommunicationType type, wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Communication Control"))
    , m_controller(nullptr)
{
    auto *sizer = new wxGridBagSizer(4, 4);
    Add(sizer, 1, wxEXPAND | wxALL, 0);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    m_openButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Open"));
    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_openButton, 1, wxEXPAND | wxALL, 0);

    auto &factory = CommunicationControllerFactory::singleton();
    m_controller = factory.CreateCommunicationController(type, GetStaticBox());

    sizer->Add(m_controller, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(buttonSizer, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);

    m_openButton->Bind(wxEVT_BUTTON, &CommunicationControlBox::OnOpen, this);
}

CommunicationController *CommunicationControlBox::GetController() const
{
    return m_controller;
}

sigslot::signal<> &CommunicationControlBox::GetInvokeOpenSignal()
{
    return m_invokeOpenSignal;
}

void CommunicationControlBox::SetOpenButtonLabel(const wxString &label)
{
    m_openButton->SetLabel(label);
}

void CommunicationControlBox::OnOpen(wxCommandEvent &event)
{
    wxUnusedVar(event);
    m_invokeOpenSignal();
}
