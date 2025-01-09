﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "SocketClientController.h"

class UDPClientController : public SocketClientController
{
public:
    UDPClientController(wxWindow *parent = nullptr);
    ~UDPClientController();

protected:
    Communication *CreateCommunication() override;
    void AboutToOpen(Communication *communication) override;
    void AboutToClose(Communication *communication) override;
};