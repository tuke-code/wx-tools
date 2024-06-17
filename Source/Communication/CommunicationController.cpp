/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationController.h"

CommunicationController::CommunicationController(wxWindow *parent)
    : wxGridBagSizer(4, 4)
{}

CommunicationController::~CommunicationController() {}

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

Communication *CommunicationController::CreateCommunication()
{
    return nullptr;
}

void CommunicationController::AboutToOpen(Communication *communication)
{
    // Nothing to do
}

void CommunicationController::AboutToClose(Communication *communication)
{
    // Nothing to do
}