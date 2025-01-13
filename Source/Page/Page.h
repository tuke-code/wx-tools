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

class IOPanel;
class ControlPanel;
class ControlPanelInput;
class ControlPanelLink;
class ControlPanelOutput;
class Page : public wxPanel
{
public:
    Page(LinkType type, wxWindow *parent);

    void Load(const wxToolsJson &json);
    wxToolsJson Save() const;

private:
    ControlPanelInput *m_inputControlBox;
    ControlPanel *m_controlBoxes;
    ControlPanelLink *m_linkControlBox;
    IOPanel *m_ioPanel;
    wxTimer m_sendTimer;
    ControlPanelOutput *m_outputControlBox;

private:
    struct ParameterKeys
    {
        const std::string linkControlBox{"LinkControlBox"};
        const std::string outputControlBox{"OutputController"};
        const std::string inputControlBox{"InputController"};
    } m_parameterKeys;

private:
    void OnInvokeOpen();
    void OnInvokeWrite(TextFormat format);
    void OnInvokeStartTimer(int ms);
    void OnBytesRead(wxToolsConstBuffer &bytes, const wxString &from);
    void OnBytesWritten(wxToolsConstBuffer &bytes, const wxString &to);
    void OnSendTimerTimeout();
    void OnClear();
    void OnTextFormatChanged(TextFormat format);

    void OutputText(wxToolsConstBuffer &bytes, const wxString &fromTo, bool isRx);
};
