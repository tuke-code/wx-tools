/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationControlBox.h"

#include <wx/gbsizer.h>
#include <wx/popupwin.h>

#include "Communication/CommunicationController.h"
#include "Communication/CommunicationControllerFactory.h"
#include "CommunicationPopup.h"

CommunicationControlBox::CommunicationControlBox(CommunicationType type, wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Communication Control"))
    , m_controller(nullptr)
    , m_popup(nullptr)
{
    auto &factory = CommunicationControllerFactory::singleton();
    m_controller = factory.CreateCommunicationController(type, GetStaticBox());
    Add(m_controller, 0, wxEXPAND, 0);

    AddSpacer(4);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    m_popup = new CommunicationPopup(parent, wxBORDER_STATIC);
    settingsButton->Bind(wxEVT_BUTTON, [this, settingsButton](wxCommandEvent &event) {
        int width = settingsButton->GetSize().GetWidth();
        m_popup->SetPosition(settingsButton->ClientToScreen(wxPoint(width, 0)));
        if (m_popup->IsShown()) {
            m_popup->Hide();
        } else {
            m_popup->Show();
        }
    });

    m_openButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Open"));
    m_openButton->Bind(wxEVT_BUTTON, &CommunicationControlBox::OnOpen, this);

    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(m_openButton, 1, wxEXPAND | wxALL, 0);
    Add(buttonSizer, 0, wxEXPAND, 0);
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
#if 0
    static wxPopupTransientWindow *popup = new wxPopupTransientWindow(m_openButton, wxBORDER_SIMPLE);
    popup->SetBackgroundColour(*wxWHITE);
    popup->SetPosition(m_openButton->ClientToScreen(wxPoint(m_openButton->GetSize().GetWidth(), 0)));
    popup->Show();
#endif

    wxUnusedVar(event);
    m_invokeOpenSignal();
}
