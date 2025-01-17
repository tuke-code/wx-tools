/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Application.h"

#include "Common/wxTools.h"
#include "MainWindow.h"

bool Application::OnInit()
{
    SetAppName("wxTools");
    SetVendorName("xTools");

#if 0
    InitGoogleLog("wxTools");
#endif
    wxToolsInfo() << "Application::OnInit()";

    auto* mainWindow = new MainWindow();
#if 0
    mainWindow->SetTransparent(50);
#endif
    mainWindow->Show(true);
    return true;
}
