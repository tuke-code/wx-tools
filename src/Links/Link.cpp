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

}

bool Link::Open()
{
    Close();

    std::thread t(&Link::Loop, this);
    t.detach();

    while (!d->isRunning.load()) {
        // wait for the thread to start
    }

    return true;
}

void Link::Close()
{
    if (d) {
        d->invokedInterrupted.store(true);
        while (d->isRunning.load()) {
            // wait for the thread to stop
        };
        d->txBytes.clear();
    }
}

void Link::Write(std::shared_ptr<char> bytes, int len)
{
    if (len > 0) {
        d->txBytes.push_back(std::make_pair(std::move(bytes), len));
    }
}

void Link::Loop()
{
    d->invokedInterrupted.store(false);
    d->isRunning.store(true);
    while (!d->invokedInterrupted.load()) {
        // do something
    }

    d->isRunning.store(false);
}
