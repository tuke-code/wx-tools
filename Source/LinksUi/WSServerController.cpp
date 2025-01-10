/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSServerController.h"

WSServerController::WSServerController(wxWindow *parent)
    : SocketServerController(parent)
{
    std::vector<void (SocketBaseController::*)(int, wxWindow *)> funcs;
    funcs.push_back(&WSServerController::InitServerComboBox);
    funcs.push_back(&WSServerController::InitServerPortCtrl);
    funcs.push_back(&WSServerController::InitClientsComboBox);
    funcs.push_back(&WSServerController::InitClearClientButton);

    InitUiComponents(funcs, parent);
}

WSServerController::~WSServerController() {}
