/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Page.h"

#include <fmt/format.h>
#include <wx/gbsizer.h>

#include "Common/wxTools.h"
#include "Links/Link.h"
#include "LinksUi/LinkUi.h"
#include "LinksUi/SocketServerUi.h"
#include "PageSettingsLink.h"

#include "PageIO.h"
#include "PageIOInput.h"
#include "PageIOOutput.h"
#include "PageSettings.h"
#include "PageSettingsInput.h"
#include "PageSettingsInputPopup.h"
#include "PageSettingsLinkPopup.h"
#include "PageSettingsOutput.h"
#include "PageSettingsOutputPopup.h"

IMPLEMENT_ABSTRACT_CLASS(Page, wxPanel)
BEGIN_EVENT_TABLE(Page, wxPanel)
EVT_THREAD(wxtBytesRx, Page::OnBytesRx)
EVT_THREAD(wxtBytesTx, Page::OnBytesTx)
EVT_THREAD(wxtErrorOccurred, Page::OnErrorOccurred)
EVT_THREAD(wxtNewClient, Page::OnNewClient)
EVT_THREAD(wxtDeleteClient, Page::OnDeleteClient)
END_EVENT_TABLE()

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
    linkSettings->GetOpenButton()->Bind(wxEVT_BUTTON, &Page::OnInvokeOpenOrClose, this);

    PageSettingsLinkPopup *linkSettingsPopup = linkSettings->GetPopup();
    linkSettingsPopup->refreshSignal.connect(&LinkUi::Refresh, linkSettings->GetLinkUi());

    PageSettingsOutput *outputSettings = m_pageSettings->GetOutputSettings();
    outputSettings->clearSignal.connect(&Page::OnClear, this);

    m_sendTimer.Bind(wxEVT_TIMER, [this](wxTimerEvent &event) { OnSendTimerTimeout(); });
}

void Page::Load(const wxtJson &json)
{
    PageParameterKeys keys;
    if (json.contains(keys.settings)) {
        m_pageSettings->Load(json[keys.settings].get<wxtJson>());
    }

    if (json.contains(keys.io)) {
        m_pageIO->Load(json[keys.io].get<wxtJson>());
    }

    int format = m_pageSettings->GetInputSettings()->GetTextFormat();
    m_pageIO->GetInput()->SetTextFormat(static_cast<TextFormat>(format));
}

wxtJson Page::Save() const
{
    wxtJson json;
    PageParameterKeys keys;
    json[keys.settings] = m_pageSettings->Save();
    json[keys.io] = m_pageIO->Save();
    return json;
}

void Page::OnInvokeOpenOrClose(wxCommandEvent &)
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
    LinkUi *linkUi = linkSettings->GetLinkUi();
    if (!linkUi->IsOpen()) {
        wxMessageBox(_("Link is not opened."), _("Error"), wxICON_ERROR);
        return;
    }

    PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
    PageSettingsInputPopup *inputSettingsPopup = inputSettings->GetPopup();
    wxtJson inputParameters = inputSettingsPopup->Save();

    PageSettingsInputPopupParameterKeys keys;
    int prefix = inputParameters[keys.prefix].get<int>();
    int suffix = inputParameters[keys.suffix].get<int>();
    int escIndex = inputParameters[keys.escIndex].get<int>();
    int startIndex = inputParameters[keys.startIndex].get<int>();
    int endIndex = inputParameters[keys.endIndex].get<int>();
    int algorithm = inputParameters[keys.algorithm].get<int>();
    bool addCrc = inputParameters[keys.addCrc].get<bool>();
    bool bigEndian = inputParameters[keys.bigEndian].get<bool>();

    Link *link = linkUi->GetLink();
    wxString text = m_pageIO->GetInput()->GetInputText();
    if (text.IsEmpty()) {
        return;
    }

    text = GetEscapeString(text.ToStdString(), escIndex);
    int len = 0;
    auto bytes = DoEncodeBytes(text.ToStdString(), len, static_cast<int>(format));
    if (len <= 0) {
        return;
    }

    std::vector<char> prefixChars = GetAdditionChars(prefix);
    std::vector<char> crcChars;
    if (addCrc) {
        crcChars = DoCalculateCRC(bytes, len, algorithm, startIndex, endIndex, bigEndian);
    }
    std::vector<char> suffixChars = GetAdditionChars(suffix);

    std::vector<char> tmp = prefixChars;
    for (int i = 0; i < len; i++) {
        tmp.push_back(bytes.get()[i]);
    }
    tmp.insert(tmp.end(), crcChars.begin(), crcChars.end());
    tmp.insert(tmp.end(), suffixChars.begin(), suffixChars.end());

    std::shared_ptr<char> allBytes(new char[tmp.size()], [](char *p) { delete[] p; });
    memcpy(allBytes.get(), tmp.data(), tmp.size());
    link->Write(std::move(allBytes), tmp.size());
}

void Page::OnInvokeStartTimer(int ms)
{
    if (ms == -1) {
        m_sendTimer.Stop();
        return;
    }

    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    LinkUi *linkUi = linkSettings->GetLinkUi();
    if (!linkUi->IsOpen()) {
        PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
        inputSettings->SetCycleIntervalComboBoxSelection(0);
        wxMessageBox(_("Link is not open."), _("Error"), wxICON_ERROR);
        return;
    }

    m_sendTimer.Start(ms);
}

void Page::OnBytesRx(wxThreadEvent &e)
{
    wxtDataItem item = e.GetPayload<wxtDataItem>();
    OutputText(item.data, item.len, item.flag, true);
}

void Page::OnBytesTx(wxThreadEvent &e)
{
    auto item = e.GetPayload<wxtDataItem>();
    OutputText(item.data, item.len, item.flag, false);
}

void Page::OnErrorOccurred(wxThreadEvent &e)
{
    Close();
    wxLogWarning(_("Error: ") + wxString::FromUTF8(e.GetString()));
}

void Page::OnNewClient(wxThreadEvent &e)
{
    auto linkUi = m_pageSettings->GetLinkSettings()->GetLinkUi();
    if (!dynamic_cast<SocketServerUi *>(linkUi)) {
        return;
    }

    auto serverUi = dynamic_cast<SocketServerUi *>(linkUi);
    wxString ip = e.GetString();
    int port = e.GetInt();
    serverUi->DoNewClient(ip.ToStdString(), port);
}

void Page::OnDeleteClient(wxThreadEvent &e)
{
    auto linkUi = m_pageSettings->GetLinkSettings()->GetLinkUi();
    if (!dynamic_cast<SocketServerUi *>(linkUi)) {
        return;
    }

    auto serverUi = dynamic_cast<SocketServerUi *>(linkUi);
    wxString ip = e.GetString();
    int port = e.GetInt();
    serverUi->DoDeleteClient(ip.ToStdString(), port);
}

void Page::OnSendTimerTimeout()
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    PageSettingsInput *inputSettings = m_pageSettings->GetInputSettings();
    if (!linkSettings->GetLinkUi()->IsOpen()) {
        return;
    }

    OnInvokeWrite(static_cast<TextFormat>(inputSettings->GetTextFormat()));
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
        stringStream << "Tx" << ("->") << fromTo;
    }

    return stringStream.str();
}

void Page::OutputText(std::shared_ptr<char> bytes, int len, std::string &fromTo, bool isRx)
{
    PageSettingsOutput *outputSettings = m_pageSettings->GetOutputSettings();
    TextFormat outputFormat = outputSettings->GetTextFormat();
    bool showDate = outputSettings->GetShowDate();
    bool showTime = outputSettings->GetShowTime();
    bool showMs = outputSettings->GetShowMs();
    bool showRx = outputSettings->GetShowRx();
    bool showTx = outputSettings->GetShowTx();
    bool showFlag = outputSettings->GetShowFlag();
    std::string text = DoDecodeBytes(bytes, len, static_cast<int>(outputFormat));
    std::string dateTimeString = ::dateTimeString(showDate, showTime, showMs);
    std::string flagString = ::flagString(isRx, fromTo, showFlag);

    if (isRx && !showRx) {
        return;
    }

    if (!isRx && !showTx) {
        return;
    }

    // Replace '\n' with '\\n' and replace '\r' with '\\r'
    wxString textCopy = text;
    textCopy.Replace("\n", "\\n");
    textCopy.Replace("\r", "\\r");
    text = textCopy.ToStdString();

    wxString str;
    if (dateTimeString.empty()) {
        str = wxString::Format("[%s] %s", flagString, text);
    } else {
        str = wxString::Format("[%s %s] %s", dateTimeString, flagString, text);
    }

    // Filter
    PageSettingsOutputPopup *outputPopup = outputSettings->GetPopup();
    wxArrayString filter = outputPopup->GetFilter();
    if (filter.IsEmpty()) {
        m_pageIO->GetOutput()->AppendText(str);
    } else {
        for (size_t i = 0; i < filter.GetCount(); i++) {
            if (str.Contains(filter[i])) {
                m_pageIO->GetOutput()->AppendText(str);
                break;
            }
        }
    }
}

void Page::Open()
{
    PageSettingsLink *linkSettings = m_pageSettings->GetLinkSettings();
    LinkUi *linkUi = linkSettings->GetLinkUi();
    if (linkUi->Open(GetEventHandler())) {
        linkUi->Disable();
        linkSettings->SetOpenButtonLabel(_("Close"));
        wxtInfo() << "Open link successfully.";
    } else {
        wxMessageBox(_("Failed to open link."), _("Error"), wxICON_ERROR);
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
    linkUi->Close();
    linkUi->Enable();
    linkSettings->SetOpenButtonLabel(_("Open"));
    wxtInfo() << "Close link successfully.";
}
