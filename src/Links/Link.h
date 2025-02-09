/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <nlohmann/json.hpp>
#include <sigslot/signal.hpp>

#include <wx/thread.h>
#include <wx/wx.h>

#include "Common/wxTools.h"

#define wxtIgnoreCloseErrorPopup 1

enum LinkEvent {
    wxtBytesTx = wxID_HIGHEST + 1,
    wxtBytesRx,
    wxtErrorOccurred,
    wxtNewClient,
    wxtDeleteClient,
    wxtLinkOpened,
    wxtLinkClosed
};

class LinkPrivate;
class Link : public wxThread
{
public:
    Link(LinkPrivate *d);
    virtual ~Link();

    bool Open();
    void Close();
    void Write(std::shared_ptr<char> bytes, int len);
    void SetEvtHandler(wxEvtHandler *handler);

    virtual void Load(const wxtJson &parameters) = 0;
    virtual wxtJson Save() = 0;

public:
    template<typename T>
    T GetD() const
    {
        return reinterpret_cast<T>(this->d);
    }

protected:
    void *Entry() final;

protected:
    LinkPrivate *d;
};
