/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPServerController.h"

UDPServerController::UDPServerController(wxWindow *parent)
    : SocketServerController(parent)
{
    std::vector<void (SocketBaseController::*)(int, wxWindow *)> funcs;
    funcs.push_back(&UDPServerController::InitServerComboBox);
    funcs.push_back(&UDPServerController::InitServerPortCtrl);
    funcs.push_back(&UDPServerController::InitClientsComboBox);
    funcs.push_back(&UDPServerController::InitClearClientButton);

    InitUiComponents(funcs, parent);
}

UDPServerController::~UDPServerController() {}
