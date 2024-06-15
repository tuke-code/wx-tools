﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "CommunicationController.h"

class SerialPortController : public CommunicationController
{
public:
    SerialPortController(wxWindow *parent = nullptr);
    ~SerialPortController();

private:
    void InitPortNameComboBox(const wxString &label, int row, wxWindow *parent);
    void InitBaudRateComboBox(const wxString &label, int row, wxWindow *parent);
    void InitDataBitsComboBox(const wxString &label, int row, wxWindow *parent);
    void InitStopBitsComboBox(const wxString &label, int row, wxWindow *parent);
    void InitParityComboBox(const wxString &label, int row, wxWindow *parent);
    void InitFlowBitsComboBox(const wxString &label, int row, wxWindow *parent);
};
