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
    , m_userNameTextEntry{nullptr}
    , m_passwordTextEntry{nullptr}
{
    InitClientComboBox(wxT("Client addres"), 0, parent);
    InitClientPortCtrl(wxT("Client port"), 1, parent);
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
