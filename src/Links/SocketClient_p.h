/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "SocketBase_p.h"

class SocketClientPrivate : public SocketBasePrivate
{
public:
    void DoPoll(struct mg_connection *c, int ev, void *ev_data) override
    {
        auto *q = reinterpret_cast<UDPClient *>(c->mgr->userdata);
        wxASSERT_MSG(q, "q is nullptr");

        if (ev == MG_EV_OPEN) {
            OnMgEvOpen(c, ev_data, q);
        } else if (ev == MG_EV_READ) {
            OnMgEvRead(c, ev_data, q);
        } else if (ev == MG_EV_POLL) {
            OnMgEvPoll(c, ev_data, q);
        } else if (ev == MG_EV_CLOSE) {
            OnMgEvClose(c, ev_data, q);
        }
    }
};
