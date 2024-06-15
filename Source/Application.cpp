/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Application.h"

#include "Common/Log.h"
#include "MainWindow.h"

bool Application::OnInit()
{
    InitGoogleLog("eTools");

    LogInfo("Application::OnInit()");

    auto* mainWindow = new MainWindow();
    mainWindow->Show(true);
    return true;
}