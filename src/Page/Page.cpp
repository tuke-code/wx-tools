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
#include "Links/Link.h"
#include "LinksUi/LinkUi.h"
#include "PageSettingsLink.h"

#include "PageIO.h"
#include "PageIOInput.h"
#include "PageIOOutput.h"
#include "PageSettings.h"
#include "PageSettingsInput.h"
#include "PageSettingsOutput.h"

Page::Page(LinkType type, wxWindow *parent)
    : wxPanel(parent, wxID_ANY)
    , m_pageSettings(nullptr)
    , m_pageIO(nullptr)
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizerAndFit(sizer);

    m_pageSettings = new PageSettings(type, this);
    sizer->Add(m_pageSettings, 0, wxEXPAND | wxALL, 4);

    m_pageIO = new PageIO(this);
    sizer->Add(m_pageIO, 1, wxEXPAND | wxALL, 4);
    Layout();

    PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
    inputSettings->invokeWriteSignal.connect(&Page::OnInvokeWrite, this);
    inputSettings->invokeStartTimerSignal.connect(&Page::OnInvokeStartTimer, this);
    inputSettings->textFormatChangedSignal.connect(&Page::OnTextFormatChanged, this);

    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    linkSettings->invokeOpenSignal.connect(&Page::OnInvokeOpenOrClose, this);

    PageSettingsOutput *outputSettings = m_pageSettings->GetOutputSettings();
    outputSettings->clearSignal.connect(&Page::OnClear, this);

    m_sendTimer.Bind(wxEVT_TIMER, [this](wxTimerEvent &event) { OnSendTimerTimeout(); });
}

void Page::Load(const wxtJson &json)
{
    PageParameterKeys keys;
    m_pageSettings->Load(json[keys.settings].get<wxtJson>());
}

wxtJson Page::Save() const
{
    wxtJson json;
    PageParameterKeys keys;
    json[keys.settings] = m_pageSettings->Save();
    return json;
}

void Page::OnInvokeOpenOrClose()
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    LinkUi *linkUi = linkSettings->GetLinkUi();
    if (linkUi->IsOpen()) {
        Close();
    } else {
        Open();
    }
}

void Page::OnInvokeWrite(TextFormat format)
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    LinkUi *communicationController = linkSettings->GetLinkUi();
    if (!communicationController->IsOpen()) {
        wxMessageBox(wxT("Communication is not open."), wxT("Error"), wxICON_ERROR);
        return;
    }

    Link *communication = communicationController->GetLink();
    wxString text = m_pageIO->GetInput()->GetInputText();

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

    PageSettingsLink *communicationControlBox = m_pageSettings->GetLinkSettings();
    LinkUi *communicationController = communicationControlBox->GetLinkUi();
    if (!communicationController->IsOpen()) {
        PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
        inputSettings->SetCycleIntervalComboBoxSelection(0);
        wxMessageBox(wxT("Communication is not open."), wxT("Error"), wxICON_ERROR);
        return;
    }

    m_sendTimer.Start(ms);
}

void Page::OnBytesRx(std::shared_ptr<char> bytes, int len, std::string from)
{
    OutputText(bytes, len, from, true);
}

void Page::OnBytesTx(std::shared_ptr<char> bytes, int len, std::string to)
{
    OutputText(bytes, len, to, false);
}

void Page::OnErrorOccurred(std::string message)
{
    Close();
    wxLogWarning(wxT("Error: ") + wxString::FromAscii(message.c_str()));
}

void Page::OnSendTimerTimeout()
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
    if (!linkSettings->GetLinkUi()->IsOpen()) {
        return;
    }

    PageSettingsInputParameterKeys keys;
    wxtJson json = inputSettings->Save();
    int textFromat = json[keys.textFormat].get<int>();
    TextFormat format = static_cast<TextFormat>(textFromat);
    OnInvokeWrite(format);
}

void Page::OnClear()
{
    m_pageIO->GetOutput()->Clear();
}

void Page::OnTextFormatChanged(TextFormat format)
{
    m_pageIO->GetInput()->SetTextFormat(format);
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

void Page::OutputText(std::shared_ptr<char> bytes, int len, std::string &fromTo, bool isRx)
{
    PageSettingsOutput *outputControlBox = m_pageSettings->GetOutputSettings();
    TextFormat outputFormat = outputControlBox->GetTextFormat();
    bool showDate = outputControlBox->GetShowDate();
    bool showTime = outputControlBox->GetShowTime();
    bool showMs = outputControlBox->GetShowMs();
    bool showRx = outputControlBox->GetShowRx();
    bool showTx = outputControlBox->GetShowTx();
    bool showFlag = outputControlBox->GetShowFlag();
    std::string text = DoDecodeBytes(bytes, len, static_cast<int>(outputFormat));
    std::string dateTimeString = ::dateTimeString(showDate, showTime, showMs);
    std::string flagString = ::flagString(isRx, fromTo, showFlag);

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

    m_pageIO->GetOutput()->AppendText(str);
}

void Page::Open()
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    LinkUi *linkUi = linkSettings->GetLinkUi();
    if (linkUi->Open()) {
        linkUi->Disable();
        linkSettings->SetOpenButtonLabel(wxT("Close"));
        wxtInfo() << "Open link successfully.";

        Link *link = linkUi->GetLink();
        link->bytesRxSignal.connect(&Page::OnBytesRx, this);
        link->bytesTxSignal.connect(&Page::OnBytesTx, this);
        link->errorOccurredSignal.connect(&Page::OnErrorOccurred, this);
    } else {
        wxMessageBox(wxT("Failed to open link."), wxT("Error"), wxICON_ERROR);
    }
}

void Page::Close()
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    LinkUi *linkUi = linkSettings->GetLinkUi();
    m_sendTimer.Stop();

    PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
    inputSettings->SetCycleIntervalComboBoxSelection(0);

    Link *link = linkUi->GetLink();
    link->bytesTxSignal.disconnect_all();
    link->bytesRxSignal.disconnect_all();
    link->errorOccurredSignal.disconnect_all();

    linkUi->Close();
    linkUi->Enable();
    linkSettings->SetOpenButtonLabel(wxT("Open"));
    wxtInfo() << "Close link successfully.";
}
