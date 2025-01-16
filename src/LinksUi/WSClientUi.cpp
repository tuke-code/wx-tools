/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSClientUi.h"

WSClientUi::WSClientUi(wxWindow *parent)
    : SocketClientUi(parent)
{
    std::vector<void (SocketBaseUi::*)(int, wxWindow *)> funcs;
    funcs.push_back(&WSClientUi::InitServerComboBox);
    funcs.push_back(&WSClientUi::InitServerPortCtrl);
    funcs.push_back(&WSClientUi::InitIsEnableAuthorizationCheckBox);
    funcs.push_back(&WSClientUi::InitDataChannelComboBox);
    funcs.push_back(&WSClientUi::InitUserNameTextCtrl);
    funcs.push_back(&WSClientUi::InitPasswordTextCtrl);

    InitUiComponents(funcs, parent);
}

WSClientUi::~WSClientUi() {}
