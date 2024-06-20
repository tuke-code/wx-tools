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
#include <wx/wx.h>

#include "Common/eTools.h"

class Communication : wxObject
{
public:
    Communication();
    ~Communication();

    sigslot::signal<asio::const_buffer &, const wxString &> &GetBytesWrittenSignal();
    sigslot::signal<asio::const_buffer &, const wxString &> &GetBytesReadSignal();

    virtual bool Open();
    virtual void Close();
    virtual void Write(const wxString &data, TextFormat format);

protected:
    sigslot::signal<asio::const_buffer &, const wxString &> m_bytesWrittenSignal;
    sigslot::signal<asio::const_buffer &, const wxString &> m_bytesReadSignal;
};
