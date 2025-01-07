/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
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

class Communication : wxObject
{
public:
    Communication();
    ~Communication();

    sigslot::signal<asio::const_buffer & /*bytes*/, const wxString & /*to*/> bytesWrittenSignal;
    sigslot::signal<asio::const_buffer & /*bytes*/, const wxString & /*from*/> bytesReadSignal;

    virtual bool Open();
    virtual void Close();
    virtual void Write(const wxString &data, TextFormat format);

    virtual void Load(const nlohmann::json &parameters);
    virtual nlohmann::json Save();

protected:
    nlohmann::json m_parameters{nlohmann::json::object()};
};
