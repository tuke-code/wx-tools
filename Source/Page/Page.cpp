/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Page.h"

#include <wx/gbsizer.h>

#include "Common/wxTools.h"
#include "PageSettingsLink.h"
#include "Links/Link.h"
#include "LinksUi/LinkUi.h"

#include "PageSettings.h"
#include "PageIO.h"
#include "PageIOInput.h"
#include "PageIOOutput.h"
#include "PageSettingsInput.h"
#include "PageSettingsOutput.h"

Page::Page(LinkType type, wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
    , m_pageSettings(nullptr)
    , m_ioSettings(nullptr)
    , m_inputSettings(nullptr)
    , m_linkControlBox(nullptr)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizerAndFit(sizer);

    m_pageSettings = new PageSettings(type, this);
    sizer->Add(m_pageSettings, 0, wxEXPAND | wxALL, 4);

    m_ioSettings = new PageIO(this);
    sizer->Add(m_ioSettings, 1, wxEXPAND | wxALL, 4);
    Layout();

    m_inputSettings = m_pageSettings->GetInputControlBox();
    m_inputSettings->invokeWriteSignal.connect(&Page::OnInvokeWrite, this);
    m_inputSettings->invokeStartTimerSignal.connect(&Page::OnInvokeStartTimer, this);
    m_inputSettings->textFormatChangedSignal.connect(&Page::OnTextFormatChanged, this);

    m_linkControlBox = m_pageSettings->GetCommunicationControlBox();
    m_linkControlBox->GetInvokeOpenSignal().connect(&Page::OnInvokeOpen, this);

    m_outputControlBox = m_pageSettings->GetOutputControlBox();
    m_outputControlBox->GetClearSignal().connect(&Page::OnClear, this);

    m_sendTimer.Bind(wxEVT_TIMER, [this](wxTimerEvent &event) { OnSendTimerTimeout(); });
}

void Page::Load(const wxToolsJson &json)
{
    wxToolsJson controllerJson = json[m_parameterKeys.linkControlBox].template get<wxToolsJson>();
    m_linkControlBox->GetController()->Load(controllerJson);
}

wxToolsJson Page::Save() const
{
    auto *linkController = m_linkControlBox->GetController();

    wxToolsJson json;
    json[m_parameterKeys.linkControlBox] = linkController->Save();
    return json;
}

void Page::OnInvokeOpen()
{
    PageSettingsLink *communicationControlBox = m_pageSettings->GetCommunicationControlBox();
    LinkUi *communicationController = communicationControlBox->GetController();
    if (communicationController->IsOpen()) {
        m_sendTimer.Stop();
        m_inputSettings->SetCycleIntervalComboBoxSelection(0);

        Link *communication = communicationController->GetLink();
        communication->emitBytesWrittenSignal.disconnect_all();

        communicationController->Close();
        communicationController->Enable();
        communicationControlBox->SetOpenButtonLabel(wxT("Open"));
        wxToolsInfo() << "Close communication successfully.";
    } else {
        if (communicationController->Open()) {
            communicationController->Disable();
            communicationControlBox->SetOpenButtonLabel(wxT("Close"));
            wxToolsInfo() << "Open communication successfully.";

            Link *communication = communicationController->GetLink();
            communication->emitBytesReadSignal.connect(&Page::OnBytesRead, this);
            communication->emitBytesWrittenSignal.connect(&Page::OnBytesWritten, this);
        } else {
            wxMessageBox(wxT("Failed to open communication."), wxT("Error"), wxICON_ERROR);
        }
    }
}

void Page::OnInvokeWrite(TextFormat format)
{
    LinkUi *communicationController = m_linkControlBox->GetController();
    if (!communicationController->IsOpen()) {
        wxMessageBox(wxT("Communication is not open."), wxT("Error"), wxICON_ERROR);
        return;
    }

    Link *communication = communicationController->GetLink();
    wxString text = m_ioSettings->GetInputBox()->GetInputText();

    if (text.IsEmpty()) {
        text = wxString::FromAscii("(null)");
    }

    communication->Write(text, format);
}

void Page::OnInvokeStartTimer(int ms)
{
    if (ms == -1) {
        m_sendTimer.Stop();
        return;
    }

    PageSettingsLink *communicationControlBox = m_pageSettings->GetCommunicationControlBox();
    LinkUi *communicationController = communicationControlBox->GetController();
    if (!communicationController->IsOpen()) {
        m_inputSettings->SetCycleIntervalComboBoxSelection(0);
        wxMessageBox(wxT("Communication is not open."), wxT("Error"), wxICON_ERROR);
        return;
    }

    m_sendTimer.Start(ms);
}

void Page::OnBytesRead(wxToolsConstBuffer &bytes, const wxString &from)
{
    OutputText(bytes, from, true);
}

void Page::OnBytesWritten(wxToolsConstBuffer &bytes, const wxString &to)
{
    OutputText(bytes, to, false);
}

void Page::OnSendTimerTimeout()
{
    if (!m_linkControlBox->GetController()->IsOpen()) {
        return;
    }

    TextFormat format = m_inputSettings->GetTextFormat();
    OnInvokeWrite(format);
}

void Page::OnClear()
{
    m_ioSettings->GetOutputBox()->Clear();
}

void Page::OnTextFormatChanged(TextFormat format)
{
    m_ioSettings->GetInputBox()->SetTextFormat(format);
}

std::string dateTimeString(bool showDate, bool showTime, bool showMs)
{
    std::string text;
    if (showDate) {
        if (showTime) {
            text = GetDateTimeString("%Y-%m-%d %H:%M:%S", showMs) + " " + text;
        } else {
            if (showMs) {
                text = GetDateTimeString("%Y-%m-%d", showMs) + " " + text;
            }
        }
    } else {
        if (showTime) {
            text = GetDateTimeString("%H:%M:%S", showMs) + " " + text;
        } else {
            if (showMs) {
                text = GetDateTimeString("%H:%M:%S", showMs) + " " + text;
            }
        }
    }

    return text;
}

std::string flagString(bool isRx, const std::string &fromTo, bool showFlag)
{
    if (!showFlag) {
        return isRx ? "Rx" : "Tx";
    }

    std::stringstream stringStream;
    if (isRx) {
        stringStream << "Rx" << ("<-") << fromTo;

    } else {
        stringStream << "Rx" << ("->") << fromTo;
    }

    return stringStream.str();
}

void Page::OutputText(wxToolsConstBuffer &bytes, const wxString &fromTo, bool isRx)
{
    PageSettingsOutput *outputControlBox = m_pageSettings->GetOutputControlBox();
    TextFormat outputFormat = outputControlBox->GetTextFormat();
    bool showDate = outputControlBox->GetShowDate();
    bool showTime = outputControlBox->GetShowTime();
    bool showMs = outputControlBox->GetShowMs();
    bool showRx = outputControlBox->GetShowRx();
    bool showTx = outputControlBox->GetShowTx();
    bool showFlag = outputControlBox->GetShowFlag();
    std::string text = DoDecodeText(bytes, outputFormat);
    std::string dateTimeString = ::dateTimeString(showDate, showTime, showMs);
    std::string flagString = ::flagString(isRx, fromTo.ToStdString(), showFlag);

    if (isRx && !showRx) {
        return;
    }

    if (!isRx && !showTx) {
        return;
    }

    wxString str;
    if (dateTimeString.empty()) {
        str = wxString::Format("[%s] %s", flagString, text);
    } else {
        str = wxString::Format("[%s %s] %s", dateTimeString, flagString, text);
    }

    m_ioSettings->GetOutputBox()->AppendText(str);
}
