/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Link.h"
#include "Link_p.h"

Link::Link(LinkPrivate *dPtr)
    : d(dPtr)
{}

Link::~Link()
{
    Close();
}

bool Link::Open()
{
    Close();

    std::thread t(&Link::Loop, this, d);
    t.detach();

    while (!d->isRunning) {
        // wait for the thread to start
        break;
    }

    return true;
}

void Link::Close()
{
    if (d) {
        d->invokedInterrupted.store(true);
        d->txBytes.clear();
        while (d->isRunning) {
            // wait for the thread to stop
            break;
        }
    }
}

void Link::Write(const wxString &data, TextFormat format)
{
    int len = 0;
    auto bytes = DoEncodeBytes(data.ToStdString(), len, static_cast<int>(format));
    if (len > 0) {
        d->txBytes.push_back(std::make_pair(std::move(bytes), len));
    }
}

void Link::Loop(LinkPrivate *d)
{
    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (1) {
        if (d->invokedInterrupted.load()) {
            break;
        }

#if 0
        // do something...
#endif

        // sleep for a while
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    d->isRunning.store(false);
}
