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
    void OnInvokeOpenOrClose();
    void OnInvokeWrite(TextFormat format);
    void OnInvokeStartTimer(int ms);
    void OnBytesRx(std::shared_ptr<char> bytes, int len, std::string from);
    void OnBytesTx(std::shared_ptr<char> bytes, int len, std::string to);
    void OnErrorOccurred(std::string message);
    void OnSendTimerTimeout();
    void OnClear();
    void OnTextFormatChanged(TextFormat format);

    void OutputText(std::shared_ptr<char> bytes, int len, std::string &fromTo, bool isRx);
    void Open();
    void Close();
};
