/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <map>
#include <wx/fileconf.h>
#include <wx/notebook.h>
#include <wx/wx.h>

#include "Common/wxTools.h"

class Page;
class MainWindow : public wxFrame
{
public:
    MainWindow();
    ~MainWindow();

private:
    void Init();
    void InitMenu();
    void InitMenuFile(wxMenuBar* menuBar);
    void InitMenuOptions(wxMenuBar* menuBar);
    void InitMenuHelp(wxMenuBar* menuBar);
    void InitStatusBar();

    void OnOpen(wxCommandEvent&);
    void OnSave(wxCommandEvent&);
    void OnSaveAs(wxCommandEvent&);
    void OnNew(wxCommandEvent&);
    void OnExit(wxCommandEvent&);

    void OnAbout(wxCommandEvent&);

    void DoLoad(wxString fileName = wxString());
    void DoSave(wxString fileName = wxString());
    void DoCheckForUpdates(wxCommandEvent&);
    void DoShowHistory(wxCommandEvent&);

private:
    std::map<LinkType, Page*> m_pageMap;
    wxStatusBar* m_statusBar;
    wxTimer m_updateTimeTimer;
    wxNotebook* m_notebook;
};
