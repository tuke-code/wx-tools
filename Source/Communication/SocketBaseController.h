/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "CommunicationController.h"

class IpComboBox;
class DataChannelComboBox;
class SocketBaseController : public CommunicationController
{
public:
    SocketBaseController(wxWindow *parent = nullptr);
    ~SocketBaseController();

private:
    wxStaticText *m_clientAddressLabel{nullptr};
    IpComboBox *m_clientComboBox{nullptr};
    wxStaticText *m_clientPortLabel{nullptr};
    wxSpinCtrl *m_clientPortCtrl{nullptr};
    wxStaticText *m_serverAddressLabel{nullptr};
    IpComboBox *m_serverComboBox{nullptr};
    wxStaticText *m_serverPortLabel{nullptr};
    wxSpinCtrl *m_serverPortCtrl{nullptr};

    wxStaticText *m_clientsLabel{nullptr};
    wxComboBox *m_clientsComboBox{nullptr};
    wxButton *m_clearClientButton{nullptr};

    wxCheckBox *m_isEnableAuthorizationCheckBox{nullptr};
    wxStaticText *m_dataChannelLabel{nullptr};
    DataChannelComboBox *m_dataChannelComboBox{nullptr};
    wxTextCtrl *m_userNameTextCtrl{nullptr};
    wxStaticText *m_userNameLabel{nullptr};
    wxTextCtrl *m_passwordTextCtrl{nullptr};
    wxStaticText *m_passwordLabel{nullptr};

private:
    void InitClientComboBox(const wxString &label, int row, wxWindow *parent);
    void InitClientPortCtrl(const wxString &label, int row, wxWindow *parent);
    void InitServerComboBox(const wxString &label, int row, wxWindow *parent);
    void InitServerPortCtrl(const wxString &label, int row, wxWindow *parent);
    void InitClientsComboBox(const wxString &label, int row, wxWindow *parent);
    void InitClearClientButton(const wxString &label, int row, wxWindow *parent);
    void InitIsEnableAuthorizationCheckBox(const wxString &label, int row, wxWindow *parent);
    void InitDataChannelComboBox(const wxString &label, int row, wxWindow *parent);
    void InitUserNameTextCtrl(const wxString &label, int row, wxWindow *parent);
    void InitPasswordTextCtrl(const wxString &label, int row, wxWindow *parent);
};
