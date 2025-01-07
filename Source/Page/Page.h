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

#include "Common/eTools.h"

class IOPanel;
class ControlBoxes;
class InputControlBox;
class CommunicationControlBox;
class OutputControlBox;
class Page : public wxPanel
{
public:
    Page(CommunicationType type, wxWindow *parent);

    void LoadParameters(const nlohmann::json &json);
    nlohmann::json SaveParameters() const;

private:
    InputControlBox *m_inputControlBox;
    ControlBoxes *m_controlBoxes;
    CommunicationControlBox *m_communicationControlBox;
    IOPanel *m_ioPanel;
    wxTimer m_sendTimer;
    OutputControlBox *m_outputControlBox;

private:
    struct ParameterNames
    {
        const std::string communicationControlBox{"CommunicationController"};
        const std::string outputControlBox{"OutputController"};
        const std::string inputControlBox{"InputController"};
    } m_parameterNames;

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
