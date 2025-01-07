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

#include "Unit/DataChannelComboBox.h"
#include "Unit/IpComboBox.h"

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
    InitClientComboBox(wxT("Client IP"), 0, parent);
    InitClientPortCtrl(wxT("Client port"), 1, parent);
    InitServerComboBox(wxT("Server IP"), 2, parent);
    InitServerPortCtrl(wxT("Server port"), 3, parent);
    InitIsEnableAuthorizationCheckBox(wxT("Enable authorization"), 4, parent);
    InitDataChannelComboBox(wxT("Channel"), 5, parent);
    InitUserNameTextCtrl(wxT("User name"), 6, parent);
    InitPasswordTextCtrl(wxT("Password"), 7, parent);
}

SocketBaseController::~SocketBaseController() {}

void SocketBaseController::InitClientComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_clientComboBox = new IpComboBox(parent);
    Add(m_clientComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitClientPortCtrl(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_clientPortCtrl = new wxSpinCtrl(parent, wxID_ANY);
    Add(m_clientPortCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitServerComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_serverComboBox = new IpComboBox(parent);
    Add(m_serverComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitServerPortCtrl(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_serverPortCtrl = new wxSpinCtrl(parent, wxID_ANY);
    Add(m_serverPortCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitIsEnableAuthorizationCheckBox(const wxString &label,
                                                             int row,
                                                             wxWindow *parent)
{
#if 0
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
#endif

    m_isEnableAuthorizationCheckBox = new wxCheckBox(parent, wxID_ANY, wxEmptyString);
    m_isEnableAuthorizationCheckBox->SetLabel(label);
    Add(m_isEnableAuthorizationCheckBox, wxGBPosition(row, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitDataChannelComboBox(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_dataChannelComboBox = new DataChannelComboBox(parent);
    Add(m_dataChannelComboBox, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitUserNameTextCtrl(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_userNameTextCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString);
    Add(m_userNameTextCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}

void SocketBaseController::InitPasswordTextCtrl(const wxString &label, int row, wxWindow *parent)
{
    auto text = new wxStaticText(parent, wxID_ANY, label);
    Add(text, wxGBPosition(row, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);

    m_passwordTextCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString);
    Add(m_passwordTextCtrl, wxGBPosition(row, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}
