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
#include <sigslot/signal.hpp>
#include <wx/jsonval.h>
#include <wx/wx.h>

#include "Common/wxTools.h"

class Links : wxObject
{
public:
    Links();
    ~Links();

    sigslot::signal<asio::const_buffer & /*bytes*/, const wxString & /*to*/> bytesWrittenSignal;
    sigslot::signal<asio::const_buffer & /*bytes*/, const wxString & /*from*/> bytesReadSignal;

    virtual bool Open();
    virtual void Close();
    virtual void Write(const wxString &data, TextFormat format);

    virtual void Load(const wxJSONValue &parameters);
    virtual wxJSONValue Save();

protected:
    wxJSONValue m_parameters{wxJSONValue(wxJSONTYPE_OBJECT)};
};
