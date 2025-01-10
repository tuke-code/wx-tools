/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "LinksController.h"

#include <wx/event.h>
#include <wx/wx.h>

LinksController::LinksController(wxWindow *parent)
    : wxGridBagSizer(4, 4)
    , m_communication(nullptr)
{}

LinksController::~LinksController() {}

Link *LinksController::GetCommunication() const
{
    return m_communication;
}

bool LinksController::Open()
{
    m_communication = CreateCommunication();
    if (!m_communication) {
        return false;
    }

    AboutToOpen(m_communication);

    return m_communication->Open();
}

void LinksController::Close()
{
    if (m_communication) {
        AboutToClose(m_communication);

        m_communication->Close();
        delete m_communication;
        m_communication = nullptr;
    }
}

bool LinksController::IsOpen() const
{
    return m_communication != nullptr;
}

void LinksController::Disable() {}

void LinksController::Enable() {}

wxJSONValue LinksController::Save() const
{
    wxJSONValue json;
    return json;
}

void LinksController::Load(const wxJSONValue &json)
{
    wxUnusedVar(json);
}

Link *LinksController::CreateCommunication()
{
    return nullptr;
}

void LinksController::AboutToOpen(Link *communication)
{
    communication->Load(Save());
}

void LinksController::AboutToClose(Link *communication)
{
    wxUnusedVar(communication);
    // Nothing to do
}
