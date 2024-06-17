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

#include "Common/Log.h"
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
{
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizerAndFit(sizer);

    m_controlBoxes = new ControlBoxes(type, this);
    sizer->Add(m_controlBoxes, 0, wxEXPAND | wxALL, 4);

    m_ioPanel = new IOPanel(this);
    sizer->Add(m_ioPanel, 1, wxEXPAND | wxALL, 4);

    InputControlBox *inputControlBox = m_controlBoxes->GetInputControlBox();
    inputControlBox->GetInvokeWriteSignal().connect(&Page::OnInvokeWrite, this);

    CommunicationControlBox *communicationControlBox = m_controlBoxes->GetCommunicationControlBox();
    communicationControlBox->GetInvokeOpenSignal().connect(&Page::OnInvokeOpen, this);
}

void Page::OnInvokeOpen()
{
    CommunicationControlBox *communicationControlBox = m_controlBoxes->GetCommunicationControlBox();
    CommunicationController *communicationController = communicationControlBox->GetController();
    if (communicationController->IsOpen()) {
        Communication *communication = communicationController->GetCommunication();
        communication->GetBytesWrittenSignal().disconnect_all();

        communicationController->Close();
        communicationControlBox->SetOpenButtonLabel(wxT("Open"));
        LogInfo("Close communication successfully.");
    } else {
        if (communicationController->Open()) {
            communicationControlBox->SetOpenButtonLabel(wxT("Close"));
            LogInfo("Open communication successfully.");

            Communication *communication = communicationController->GetCommunication();
            communication->GetBytesWrittenSignal().connect(&Page::OnBytesWritten, this);
        } else {
            // wxWidget警告对话框
            wxMessageBox(wxT("Failed to open communication."), wxT("Error"), wxICON_ERROR);
        }
    }
}

void Page::OnInvokeWrite(TextFormat format)
{
    wxString text = m_ioPanel->GetInputBox()->GetInputText();
    CommunicationControlBox *communicationControlBox = m_controlBoxes->GetCommunicationControlBox();
    CommunicationController *communicationController = communicationControlBox->GetController();
    Communication *communication = communicationController->GetCommunication();
    communication->Write(text, format);
}

void Page::OnBytesWritten(asio::const_buffer &bytes, TextFormat format, const wxString &to)
{
    OutputControlBox *outputControlBox = m_controlBoxes->GetOutputControlBox();
    wxUnusedVar(outputControlBox);

    OutputBox *outBox = m_ioPanel->GetOutputBox();
    outBox->AppendText(to);
}
