/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPClientUi.h"

#include "Links/UDPClient.h"

UDPClientUi::UDPClientUi(wxWindow *parent)
    : SocketClientUi(parent)
{
    std::vector<void (SocketBaseUi::*)(int, wxWindow *)> funcs;
    funcs.push_back(&UDPClientUi::InitServerComboBox);
    funcs.push_back(&UDPClientUi::InitServerPortCtrl);

    InitUiComponents(funcs, parent);
}

UDPClientUi::~UDPClientUi() {}

Link *UDPClientUi::CreateLink()
{
    return new UDPClient();
}

void UDPClientUi::AboutToOpen(Link *communication)
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

void UDPClientUi::AboutToClose(Link *communication)
{
    // Nothing to do yet.
}
