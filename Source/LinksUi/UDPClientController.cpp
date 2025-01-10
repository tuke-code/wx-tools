/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPClientController.h"

#include "Links/UDPClient.h"

UDPClientController::UDPClientController(wxWindow *parent)
    : SocketClientController(parent)
{
    std::vector<void (SocketBaseController::*)(int, wxWindow *)> funcs;
    funcs.push_back(&UDPClientController::InitServerComboBox);
    funcs.push_back(&UDPClientController::InitServerPortCtrl);

    InitUiComponents(funcs, parent);
}

UDPClientController::~UDPClientController() {}

Link *UDPClientController::CreateCommunication()
{
    return new UDPClient();
}

void UDPClientController::AboutToOpen(Link *communication)
{
    if (!communication) {
        return;
    }

    UDPClient *udpClient = dynamic_cast<UDPClient *>(communication);
    if (!udpClient) {
        return;
    }

    udpClient->Load(Save());
}

void UDPClientController::AboutToClose(Link *communication)
{
    // Nothing to do yet.
}
