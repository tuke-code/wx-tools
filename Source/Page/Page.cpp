/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Page.h"

#include <wx/gbsizer.h>

#include "Common/eTools.h"
#include "Communication/Communication.h"
#include "Communication/CommunicationController.h"
#include "CommunicationControlBox.h"

#include "ControlBoxes.h"
#include "IOPanel.h"
#include "InputBox.h"
#include "InputControlBox.h"
#include "OutputBox.h"
#include "OutputControlBox.h"

Page::Page(CommunicationType type, wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
    , m_controlBoxes(nullptr)
    , m_ioPanel(nullptr)
    , m_inputControlBox(nullptr)
    , m_communicationControlBox(nullptr)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizerAndFit(sizer);

    m_controlBoxes = new ControlBoxes(type, this);
    sizer->Add(m_controlBoxes, 0, wxEXPAND | wxALL, 4);

    m_ioPanel = new IOPanel(this);
    sizer->Add(m_ioPanel, 1, wxEXPAND | wxALL, 4);
    Layout();

    m_inputControlBox = m_controlBoxes->GetInputControlBox();
    m_inputControlBox->GetInvokeWriteSignal().connect(&Page::OnInvokeWrite, this);
    m_inputControlBox->GetInvokeStartTimerSignal().connect(&Page::OnInvokeStartTimer, this);
    m_inputControlBox->GetTextFormatChangedSignal().connect(&Page::OnTextFormatChanged, this);

    m_communicationControlBox = m_controlBoxes->GetCommunicationControlBox();
    m_communicationControlBox->GetInvokeOpenSignal().connect(&Page::OnInvokeOpen, this);

    m_outputControlBox = m_controlBoxes->GetOutputControlBox();
    m_outputControlBox->GetClearSignal().connect(&Page::OnClear, this);

    m_sendTimer.Bind(wxEVT_TIMER, [this](wxTimerEvent &event) { OnSendTimerTimeout(); });
}

void Page::LoadParameters(const nlohmann::json &json)
{
    auto controllerJson = json[m_parameterNames.communicationControlBox];
    m_communicationControlBox->GetController()->LoadParameters(controllerJson);
}

nlohmann::json Page::SaveParameters() const
{
    auto *communicationController = m_communicationControlBox->GetController();

    nlohmann::json json;
    json[m_parameterNames.communicationControlBox] = communicationController->SaveParameters();
    return json;
}

void Page::OnInvokeOpen()
{
    CommunicationControlBox *communicationControlBox = m_controlBoxes->GetCommunicationControlBox();
    CommunicationController *communicationController = communicationControlBox->GetController();
    if (communicationController->IsOpen()) {
        m_sendTimer.Stop();
        m_inputControlBox->SetCycleIntervalComboBoxSelection(0);

        Communication *communication = communicationController->GetCommunication();
        communication->GetBytesWrittenSignal().disconnect_all();

        communicationController->Close();
        communicationController->Enable();
        communicationControlBox->SetOpenButtonLabel(wxT("Open"));
        eToolsInfo() << "Close communication successfully.";
    } else {
        if (communicationController->Open()) {
            communicationController->Disable();
            communicationControlBox->SetOpenButtonLabel(wxT("Close"));
            eToolsInfo() << "Open communication successfully.";

            Communication *communication = communicationController->GetCommunication();
            communication->GetBytesReadSignal().connect(&Page::OnBytesRead, this);
            communication->GetBytesWrittenSignal().connect(&Page::OnBytesWritten, this);
        } else {
            wxMessageBox(wxT("Failed to open communication."), wxT("Error"), wxICON_ERROR);
        }
    }
}

void Page::OnInvokeWrite(TextFormat format)
{
    CommunicationController *communicationController = m_communicationControlBox->GetController();
    if (!communicationController->IsOpen()) {
        wxMessageBox(wxT("Communication is not open."), wxT("Error"), wxICON_ERROR);
        return;
    }

    Communication *communication = communicationController->GetCommunication();
    wxString text = m_ioPanel->GetInputBox()->GetInputText();

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

    CommunicationControlBox *communicationControlBox = m_controlBoxes->GetCommunicationControlBox();
    CommunicationController *communicationController = communicationControlBox->GetController();
    if (!communicationController->IsOpen()) {
        m_inputControlBox->SetCycleIntervalComboBoxSelection(0);
        wxMessageBox(wxT("Communication is not open."), wxT("Error"), wxICON_ERROR);
        return;
    }

    m_sendTimer.Start(ms);
}

void Page::OnBytesRead(eToolsConstBuffer &bytes, const wxString &from)
{
    OutputText(bytes, from, true);
}

void Page::OnBytesWritten(eToolsConstBuffer &bytes, const wxString &to)
{
    OutputText(bytes, to, false);
}

void Page::OnSendTimerTimeout()
{
    if (!m_communicationControlBox->GetController()->IsOpen()) {
        return;
    }

    TextFormat format = m_inputControlBox->GetTextFormat();
    OnInvokeWrite(format);
}

void Page::OnClear()
{
    m_ioPanel->GetOutputBox()->Clear();
}

void Page::OnTextFormatChanged(TextFormat format)
{
    m_ioPanel->GetInputBox()->SetTextFormat(format);
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

void Page::OutputText(eToolsConstBuffer &bytes, const wxString &fromTo, bool isRx)
{
    OutputControlBox *outputControlBox = m_controlBoxes->GetOutputControlBox();
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

    m_ioPanel->GetOutputBox()->AppendText(str);
}
