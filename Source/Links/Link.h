/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio/buffer.hpp>
#include <nlohmann/json.hpp>
#include <sigslot/signal.hpp>

#include <wx/wx.h>

#include "Common/wxTools.h"

class Link : wxObject
{
public:
    sigslot::signal<asio::const_buffer & /*bytes*/, const wxString & /*to*/> bytesWrittenSignal;
    sigslot::signal<asio::const_buffer & /*bytes*/, const wxString & /*from*/> bytesReadSignal;

    virtual bool Open() = 0;
    virtual void Close() = 0;
    virtual void Write(const wxString &data, TextFormat format) = 0;

    virtual void Load(const nlohmann::json &parameters) = 0;
    virtual nlohmann::json Save() = 0;
};
