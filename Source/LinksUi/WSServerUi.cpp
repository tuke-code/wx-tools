﻿/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSServerUi.h"

WSServerUi::WSServerUi(wxWindow *parent)
    : SocketServerUi(parent)
{
    std::vector<void (SocketBaseUi::*)(int, wxWindow *)> funcs;
    funcs.push_back(&WSServerUi::InitServerComboBox);
    funcs.push_back(&WSServerUi::InitServerPortCtrl);
    funcs.push_back(&WSServerUi::InitClientsComboBox);
    funcs.push_back(&WSServerUi::InitClearClientButton);

    InitUiComponents(funcs, parent);
}

WSServerUi::~WSServerUi() {}
