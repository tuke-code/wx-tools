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
    void OnMgEvClose(struct mg_connection *c, void *ev_data)
    {
        if (evtHandler) {
            DoQueueError(_("Client closed, server has been closed or not found."));
            DoQueueLinkClosed();
        }
    }

    void DoPoll(struct mg_connection *c, int ev, void *ev_data) override
    {
        SocketBasePrivate::DoPoll(c, ev, ev_data);
        if (ev == MG_EV_CLOSE) {
            OnMgEvClose(c, ev_data);
        } else if (ev == MG_EV_ERROR) {
            OnMgEvError(c, ev_data);
        }
    }
};
