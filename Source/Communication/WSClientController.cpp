/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSClientController.h"

WSClientController::WSClientController(wxWindow *parent)
    : SocketClientController(parent)
{
    std::vector<void (SocketBaseController::*)(int, wxWindow *)> funcs;
    funcs.push_back(&WSClientController::InitServerComboBox);
    funcs.push_back(&WSClientController::InitServerPortCtrl);
    funcs.push_back(&WSClientController::InitIsEnableAuthorizationCheckBox);
    funcs.push_back(&WSClientController::InitDataChannelComboBox);
    funcs.push_back(&WSClientController::InitUserNameTextCtrl);
    funcs.push_back(&WSClientController::InitPasswordTextCtrl);

    InitUiComponents(funcs, parent);
}

WSClientController::~WSClientController() {}
