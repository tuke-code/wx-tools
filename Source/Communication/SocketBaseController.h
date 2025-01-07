/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
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
    IpComboBox *m_clientComboBox{nullptr};
    wxSpinCtrl *m_clientPortCtrl{nullptr};
    IpComboBox *m_serverComboBox{nullptr};
    wxSpinCtrl *m_serverPortCtrl{nullptr};

    wxCheckBox *m_isEnableAuthorizationCheckBox{nullptr};
    DataChannelComboBox *m_dataChannelComboBox{nullptr};
    wxTextCtrl *m_userNameTextCtrl{nullptr};
    wxTextCtrl *m_passwordTextCtrl{nullptr};

private:
    void InitClientComboBox(const wxString &label, int row, wxWindow *parent);
    void InitClientPortCtrl(const wxString &label, int row, wxWindow *parent);
    void InitServerComboBox(const wxString &label, int row, wxWindow *parent);
    void InitServerPortCtrl(const wxString &label, int row, wxWindow *parent);
    void InitIsEnableAuthorizationCheckBox(const wxString &label, int row, wxWindow *parent);
    void InitDataChannelComboBox(const wxString &label, int row, wxWindow *parent);
    void InitUserNameTextCtrl(const wxString &label, int row, wxWindow *parent);
    void InitPasswordTextCtrl(const wxString &label, int row, wxWindow *parent);
};
