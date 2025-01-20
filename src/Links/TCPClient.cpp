/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPClient.h"
#include "TCPClient_p.h"

#include <mongoose.h>

TCPClient::TCPClient()
    : SocketClient(new TCPClientPrivate)
{}

TCPClient::~TCPClient()
{
    delete GetD<TCPClientPrivate>();
}

void TCPClient::Loop()
{
    struct mg_mgr mgr;
    struct mg_connection *c;
    mg_log_set(MG_LL_NONE);
    mg_mgr_init(&mgr);
}
