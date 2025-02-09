/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Application.h"

#include <mongoose.h>
#include <wx/stdpaths.h>

#include "Common/wxTools.h"
#include "MainWindow.h"

#if defined(WXT_RELEASE)
#if defined(WIN32)
// clang-format off
#include <windows.h>
#include <DbgHelp.h>
// clang-format on

static LONG stUnhandledExceptionFilter(EXCEPTION_POINTERS *ExceptionInfo)
{
    wxUnusedVar(ExceptionInfo);

    // Remove the settings file
    wxString settingsFile = GetSettingsFileName();
    if (wxFileExists(settingsFile)) {
        wxRemoveFile(settingsFile);
    }

    return EXCEPTION_EXECUTE_HANDLER;
}
#endif
#endif

bool Application::OnInit()
{
    SetAppName("wxTools");
    SetVendorName("xTools");
    mg_log_set(MG_LL_NONE);

#if defined(WXT_RELEASE)
#if defined(WIN32)
    SetUnhandledExceptionFilter(stUnhandledExceptionFilter);
#endif
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
    wxtInfo() << "--------------------------------------------------------------------------------";

    auto* mainWindow = new MainWindow();
#if 0
    mainWindow->SetTransparent(50);
#endif
    mainWindow->Show(true);
    return true;
}

Application::~Application()
{
#if defined(WXT_RELEASE)
    DoShutdownLogging();
#endif
}
