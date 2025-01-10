﻿/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "SocketBaseController.h"

#include <wx/spinctrl.h>
#include <wx/textctrl.h>

#include "Links/SocketBase.h"
#include "Utilities/DataChannelComboBox.h"
#include "Utilities/IpComboBox.h"

SocketBaseController::SocketBaseController(wxWindow *parent)
    : LinksController(parent)
    , m_clientComboBox{nullptr}
    , m_clientPortCtrl{nullptr}
    , m_serverComboBox{nullptr}
    , m_serverPortCtrl{nullptr}
    , m_isAuthorizationCheckBox{nullptr}
    , m_dataChannelComboBox{nullptr}
    , m_userNameTextCtrl{nullptr}
    , m_passwordTextCtrl{nullptr}
{}

SocketBaseController::~SocketBaseController() {}

void SocketBaseController::Disable()
{
    if (m_clientComboBox) {
        m_clientComboBox->Disable();
    }
    if (m_clientPortCtrl) {
        m_clientPortCtrl->Disable();
    }
    if (m_serverComboBox) {
        m_serverComboBox->Disable();
    }
    if (m_serverPortCtrl) {
        m_serverPortCtrl->Disable();
    }
    if (m_isAuthorizationCheckBox) {
        m_isAuthorizationCheckBox->Disable();
    }
    if (m_userNameTextCtrl) {
        m_userNameTextCtrl->Disable();
    }
    if (m_passwordTextCtrl) {
        m_passwordTextCtrl->Disable();
    }
}

void SocketBaseController::Enable()
{
    if (m_clientComboBox) {
        m_clientComboBox->Enable();
    }
    if (m_clientPortCtrl) {
        m_clientPortCtrl->Enable();
    }
    if (m_serverComboBox) {
        m_serverComboBox->Enable();
    }
    if (m_serverPortCtrl) {
        m_serverPortCtrl->Enable();
    }
    if (m_isAuthorizationCheckBox) {
        m_isAuthorizationCheckBox->Enable();
    }
    if (m_userNameTextCtrl) {
        m_userNameTextCtrl->Enable();
    }
    if (m_passwordTextCtrl) {
        m_passwordTextCtrl->Enable();
    }
}

nlohmann::json SocketBaseController::Save() const
{
    nlohmann::json json;
    SocketBaseParameterKeys keys;
    // clang-format off
    json[keys.clientAddress] = m_clientComboBox ? m_clientComboBox->GetValue() : "127.0.0.1";
    json[keys.clientPort] = m_clientPortCtrl ? m_clientPortCtrl->GetValue() : 54321;
    json[keys.serverAddress] = m_serverComboBox ? m_serverComboBox->GetValue() : "127.0.0.1";
    json[keys.serverPort] = m_serverPortCtrl ? m_serverPortCtrl->GetValue() : 54321;
    json[keys.isAuthorization] = m_isAuthorizationCheckBox ? m_isAuthorizationCheckBox->GetValue() : false;
    json[keys.dataChannel] = m_dataChannelComboBox ? m_dataChannelComboBox->GetSelection() : 0;
    json[keys.userName] = m_userNameTextCtrl ? m_userNameTextCtrl->GetValue() : "";
    json[keys.password] = m_passwordTextCtrl ? m_passwordTextCtrl->GetValue() : "";
    // clang-format on

    return json;
}

void SocketBaseController::Load(const nlohmann::json &json)
{
    SocketBaseParameterKeys keys;
    if (m_clientComboBox) {
        wxString clientAddress = json[keys.clientAddress].template get<std::string>();
        int section = m_clientComboBox->FindString(clientAddress);
        if (section != wxNOT_FOUND) {
            m_clientComboBox->SetSelection(section);
        }
    }
    if (m_clientPortCtrl) {
        int clientPort = json[keys.clientPort].template get<int>();
        m_clientPortCtrl->SetValue(clientPort);
    }
    if (m_serverComboBox) {
        wxString serverAddress = json[keys.serverAddress].template get<std::string>();
        int section = m_serverComboBox->FindString(serverAddress);
        if (section != wxNOT_FOUND) {
            m_serverComboBox->SetSelection(section);
        }
    }
    if (m_serverPortCtrl) {
        int serverPort = json[keys.serverPort].template get<int>();
        m_serverPortCtrl->SetValue(serverPort);
    }
    if (m_dataChannelComboBox) {
        int dataChannel = json[keys.dataChannel].template get<int>();
        m_dataChannelComboBox->SetDataChannel(dataChannel);
    }
    if (m_isAuthorizationCheckBox) {
        bool isAuthorization = json[keys.isAuthorization].template get<bool>();
        m_isAuthorizationCheckBox->SetValue(isAuthorization);
    }
    if (m_userNameTextCtrl) {
        wxString userName = json[keys.userName].template get<std::string>();
        m_userNameTextCtrl->SetValue(userName);
    }
    if (m_passwordTextCtrl) {
        wxString password = json[keys.password].template get<std::string>();
        m_passwordTextCtrl->SetValue(password);
    }
}

void SocketBaseController::InitUiComponents(
    const std::vector<void (SocketBaseController::*)(int, wxWindow *)> &funcs, wxWindow *parent)
{
    for (int i = 0; i < funcs.size(); i++) {
        (this->*funcs[i])(i, parent);
    }
}

void SocketBaseController::InitClientComboBox(int row, wxWindow *parent)
{
    m_clientAddressLabel = new wxStaticText(parent, wxID_ANY, wxT("Client IP"));
    Add(m_clientAddressLabel,
        wxGBPosition(row, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL,
        0);

    m_clientComboBox = new IpComboBox(parent);
    Add(m_clientComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitClientPortCtrl(int row, wxWindow *parent)
{
    m_clientPortLabel = new wxStaticText(parent, wxID_ANY, wxT("Client port"));
    Add(m_clientPortLabel, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_clientPortCtrl = new wxSpinCtrl(parent, wxID_ANY);
    Add(m_clientPortCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    m_clientPortCtrl->SetRange(1, 65535);
    m_clientPortCtrl->SetValue(54321);
}

void SocketBaseController::InitServerComboBox(int row, wxWindow *parent)
{
    m_serverAddressLabel = new wxStaticText(parent, wxID_ANY, wxT("Server IP"));
    Add(m_serverAddressLabel,
        wxGBPosition(row, 0),
        wxGBSpan(1, 1),
        wxALIGN_CENTER_VERTICAL | wxALL,
        0);

    m_serverComboBox = new IpComboBox(parent);
    Add(m_serverComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitServerPortCtrl(int row, wxWindow *parent)
{
    m_serverPortLabel = new wxStaticText(parent, wxID_ANY, wxT("Server port"));
    Add(m_serverPortLabel, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_serverPortCtrl = new wxSpinCtrl(parent, wxID_ANY);
    Add(m_serverPortCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    m_serverPortCtrl->SetRange(1, 65535);
    m_serverPortCtrl->SetValue(51234);
}

void SocketBaseController::InitClientsComboBox(int row, wxWindow *parent)
{
    m_clientsLabel = new wxStaticText(parent, wxID_ANY, wxT("Clients"));
    Add(m_clientsLabel, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_clientsComboBox = new wxComboBox(parent, wxID_ANY);
    Add(m_clientsComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitClearClientButton(int row, wxWindow *parent)
{
    m_clearClientButton = new wxButton(parent, wxID_ANY, wxT("Disconnect All Client"));
    Add(m_clearClientButton, wxGBPosition(row, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitIsEnableAuthorizationCheckBox(int row, wxWindow *parent)
{
    m_isAuthorizationCheckBox = new wxCheckBox(parent, wxID_ANY, wxEmptyString);
    m_isAuthorizationCheckBox->SetLabel(wxT("Enable authorization"));
    Add(m_isAuthorizationCheckBox, wxGBPosition(row, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitDataChannelComboBox(int row, wxWindow *parent)
{
    m_dataChannelLabel = new wxStaticText(parent, wxID_ANY, wxT("Channel"));
    Add(m_dataChannelLabel, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_dataChannelComboBox = new DataChannelComboBox(parent);
    Add(m_dataChannelComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitUserNameTextCtrl(int row, wxWindow *parent)
{
    m_userNameLabel = new wxStaticText(parent, wxID_ANY, wxT("User name"));
    Add(m_userNameLabel, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_userNameTextCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString);
    Add(m_userNameTextCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitPasswordTextCtrl(int row, wxWindow *parent)
{
    m_passwordLabel = new wxStaticText(parent, wxID_ANY, wxT("Password"));
    Add(m_passwordLabel, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_passwordTextCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString);
    Add(m_passwordTextCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}
