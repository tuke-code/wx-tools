/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPServerUi.h"

#include "Links/UDPServer.h"

UDPServerUi::UDPServerUi(wxWindow *parent)
    : SocketServerUi(parent)
{
    std::vector<void (SocketBaseUi::*)(int, wxWindow *)> funcs;
    funcs.push_back(&UDPServerUi::InitServerComboBox);
    funcs.push_back(&UDPServerUi::InitServerPortCtrl);
    funcs.push_back(&UDPServerUi::InitClientsComboBox);
    funcs.push_back(&UDPServerUi::InitClearClientButton);

    InitUiComponents(funcs, parent);
}

UDPServerUi::~UDPServerUi() {}

Link *UDPServerUi::CreateLink()
{
    auto *udpServer = new UDPServer();
    udpServer->newClientSignal.connect(&UDPServerUi::newClient, this);
    udpServer->deleteClientSignal.connect(&UDPServerUi::deleteClient, this);

    return udpServer;
}
