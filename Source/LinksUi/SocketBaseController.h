/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "LinksController.h"

class IpComboBox;
class DataChannelComboBox;
class SocketBaseController : public LinksController
{
public:
    SocketBaseController(wxWindow *parent = nullptr);
    ~SocketBaseController();

    void Disable() override;
    void Enable() override;
    nlohmann::json Save() const override;
    void Load(const nlohmann::json &json) override;

protected:
    // clang-format off
    void InitUiComponents(const std::vector<void (SocketBaseController::*)(int, wxWindow *)> &funcs, wxWindow *parent);
    void InitClientComboBox(int row, wxWindow *parent);
    void InitClientPortCtrl(int row, wxWindow *parent);
    void InitServerComboBox(int row, wxWindow *parent);
    void InitServerPortCtrl(int row, wxWindow *parent);
    void InitClientsComboBox(int row, wxWindow *parent);
    void InitClearClientButton(int row, wxWindow *parent);
    void InitIsEnableAuthorizationCheckBox(int row, wxWindow *parent);
    void InitDataChannelComboBox(int row, wxWindow *parent);
    void InitUserNameTextCtrl(int row, wxWindow *parent);
    void InitPasswordTextCtrl(int row, wxWindow *parent);
    // clang-format on

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

    wxCheckBox *m_isAuthorizationCheckBox{nullptr};
    wxStaticText *m_dataChannelLabel{nullptr};
    DataChannelComboBox *m_dataChannelComboBox{nullptr};
    wxTextCtrl *m_userNameTextCtrl{nullptr};
    wxStaticText *m_userNameLabel{nullptr};
    wxTextCtrl *m_passwordTextCtrl{nullptr};
    wxStaticText *m_passwordLabel{nullptr};
};
