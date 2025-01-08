/***************************************************************************************************
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

#include "Utilities/DataChannelComboBox.h"
#include "Utilities/IpComboBox.h"

SocketBaseController::SocketBaseController(wxWindow *parent)
    : CommunicationController(parent)
    , m_clientComboBox{nullptr}
    , m_clientPortCtrl{nullptr}
    , m_serverComboBox{nullptr}
    , m_serverPortCtrl{nullptr}
    , m_isEnableAuthorizationCheckBox{nullptr}
    , m_dataChannelComboBox{nullptr}
    , m_userNameTextCtrl{nullptr}
    , m_passwordTextCtrl{nullptr}
{

}

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
    if (m_isEnableAuthorizationCheckBox) {
        m_isEnableAuthorizationCheckBox->Disable();
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
    if (m_isEnableAuthorizationCheckBox) {
        m_isEnableAuthorizationCheckBox->Enable();
    }
    if (m_userNameTextCtrl) {
        m_userNameTextCtrl->Enable();
    }
    if (m_passwordTextCtrl) {
        m_passwordTextCtrl->Enable();
    }
}

wxJSONValue SocketBaseController::SaveParameters() const
{
    wxJSONValue json;

    return json;
}

void SocketBaseController::LoadParameters(const wxJSONValue &json) {}

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
#if 0
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
#endif

    m_isEnableAuthorizationCheckBox = new wxCheckBox(parent, wxID_ANY, wxEmptyString);
    m_isEnableAuthorizationCheckBox->SetLabel(wxT("Enable authorization"));
    Add(m_isEnableAuthorizationCheckBox, wxGBPosition(row, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
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
