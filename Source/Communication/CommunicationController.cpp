/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationController.h"

#include <wx/event.h>
#include <wx/wx.h>

CommunicationController::CommunicationController(wxWindow *parent)
    : wxGridBagSizer(4, 4)
    , m_communication(nullptr)
{}

CommunicationController::~CommunicationController() {}

Communication *CommunicationController::GetCommunication() const
{
    return m_communication;
}

bool CommunicationController::Open()
{
    m_communication = CreateCommunication();
    if (!m_communication) {
        return false;
    }

    AboutToOpen(m_communication);

    return m_communication->Open();
}

void CommunicationController::Close()
{
    if (m_communication) {
        AboutToClose(m_communication);

        m_communication->Close();
        delete m_communication;
        m_communication = nullptr;
    }
}

bool CommunicationController::IsOpen() const
{
    return m_communication != nullptr;
}

void CommunicationController::Disable() {}

void CommunicationController::Enable() {}

wxJSONValue CommunicationController::SaveParameters() const
{
    wxJSONValue json;
    return json;
}

void CommunicationController::LoadParameters(const wxJSONValue &json)
{
    wxUnusedVar(json);
}

Communication *CommunicationController::CreateCommunication()
{
    return nullptr;
}

void CommunicationController::AboutToOpen(Communication *communication)
{
    communication->Load(SaveParameters());
}

void CommunicationController::AboutToClose(Communication *communication)
{
    wxUnusedVar(communication);
    // Nothing to do
}
