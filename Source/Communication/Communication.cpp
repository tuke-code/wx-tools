/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Communication.h"

Communication::Communication() {}

Communication::~Communication() {}

sigslot::signal<asio::const_buffer &, const wxString &> &
Communication::GetBytesWrittenSignal()
{
    return m_bytesWrittenSignal;
}

sigslot::signal<asio::const_buffer &> &Communication::GetBytesReadSignal()
{
    return m_bytesReadSignal;
}

bool Communication::Open()
{
    return false;
}

void Communication::Close() {}

void Communication::Write(const wxString &data, TextFormat format)
{
    wxUnusedVar(data);
    wxUnusedVar(format);
}
