/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSClientUi.h"

#include "Links/WSClient.h"

WSClientUi::WSClientUi(wxWindow *parent)
    : SocketClientUi(parent)
{
    std::vector<void (SocketBaseUi::*)(int, wxWindow *)> funcs;
    funcs.push_back(&WSClientUi::InitServerComboBox);
    funcs.push_back(&WSClientUi::InitServerPortCtrl);
    funcs.push_back(&WSClientUi::InitDataChannelComboBox);
    funcs.push_back(&WSClientUi::InitIsEnableAuthorizationCheckBox);
#if 0
    funcs.push_back(&WSClientUi::InitUserNameTextCtrl);
    funcs.push_back(&WSClientUi::InitPasswordTextCtrl);
#endif
    InitUiComponents(funcs, parent);
}

WSClientUi::~WSClientUi() {}

Link *WSClientUi::NewLink()
{
    return new WSClient();
}

void WSClientUi::DeleteLink(Link *link)
{
    delete dynamic_cast<WSClient *>(link);
}
