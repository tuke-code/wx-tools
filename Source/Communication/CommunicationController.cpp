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

bool CommunicationController::openCommunication()
{
    return openCommunicationActually();
}

bool CommunicationController::openCommunicationActually()
{
    return false;
}

void CommunicationController::closeCommunication()
{
    closeCommunicationActually();
}

void CommunicationController::closeCommunicationActually() {}