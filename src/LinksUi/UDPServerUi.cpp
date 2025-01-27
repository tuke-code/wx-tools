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

    InitUiComponents(funcs, parent);
}

UDPServerUi::~UDPServerUi() {}

Link *UDPServerUi::NewLink()
{
    auto *udpServer = new UDPServer();
    udpServer->newClientSignal.connect(&UDPServerUi::DoNewClient, this);
    udpServer->deleteClientSignal.connect(&UDPServerUi::DoDeleteClient, this);

    return udpServer;
}

void UDPServerUi::DeleteLink(Link *link)
{
    auto *udpServer = dynamic_cast<UDPServer *>(link);
    if (udpServer) {
        udpServer->newClientSignal.disconnect(&UDPServerUi::DoNewClient, this);
        udpServer->deleteClientSignal.disconnect(&UDPServerUi::DoDeleteClient, this);
        delete udpServer;
    }
}
