﻿/***************************************************************************************************
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

struct PageParameterKeys
{
    std::string io = {"io"};
    std::string settings = {"settings"};
};

class PageIO;
class PageSettings;
class Page : public wxPanel
{
public:
    Page(LinkType type, wxWindow *parent);

    void Load(const wxToolsJson &json);
    wxToolsJson Save() const;

private:
    PageSettings *m_pageSettings;
    PageIO *m_pageIO;
    wxTimer m_sendTimer;

private:
private:
    void OnInvokeOpen();
    void OnInvokeWrite(TextFormat format);
    void OnInvokeStartTimer(int ms);
    void OnBytesRead(const wxToolsConstBuffer &bytes, const wxString &from);
    void OnBytesWritten(const wxToolsConstBuffer &bytes, const wxString &to);
    void OnSendTimerTimeout();
    void OnClear();
    void OnTextFormatChanged(TextFormat format);

    void OutputText(const wxToolsConstBuffer &bytes, const wxString &fromTo, bool isRx);
};
