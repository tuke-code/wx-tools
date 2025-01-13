/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPServerController.h"

TCPServerController::TCPServerController(wxWindow *parent)
    : SocketServerController(parent)
{
    std::vector<void (SocketBaseController::*)(int, wxWindow *)> funcs;
    funcs.push_back(&TCPServerController::InitServerComboBox);
    funcs.push_back(&TCPServerController::InitServerPortCtrl);
    funcs.push_back(&TCPServerController::InitClientsComboBox);
    funcs.push_back(&TCPServerController::InitClearClientButton);

    InitUiComponents(funcs, parent);
}

TCPServerController::~TCPServerController() {}
