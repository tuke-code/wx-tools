/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Application.h"

#include <wx/stdpaths.h>

#include "Common/wxTools.h"
#include "MainWindow.h"

bool Application::OnInit()
{
    SetAppName("wxTools");
    SetVendorName("xTools");

#if 0 //defined(WXT_RELEASE)
    DoInitLogging("wxTools");
#endif
    auto stdPath = wxStandardPaths::Get();
    wxString i18nDir = stdPath.GetDataDir();
    i18nDir += wxFileName::GetPathSeparator();
    i18nDir += wxString("i18n");

    m_locale.AddCatalogLookupPathPrefix(i18nDir);
    m_locale.Init(wxLANGUAGE_DEFAULT, wxLOCALE_LOAD_DEFAULT);
    m_locale.AddCatalog(wxString("wxTools"));
    m_locale.AddCatalog(wxString("wxWidgets"));
    wxtInfo() << "Applicationn booting...";

    auto* mainWindow = new MainWindow();
    mainWindow->Show(true);
    return true;
}

Application::~Application()
{
#if defined(WXT_RELEASE)
    DoShutdownLogging();
#endif
}
