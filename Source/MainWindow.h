﻿/***************************************************************************************************
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
#include <wx/wx.h>

#include "Common/wxTools.h"

class Page;
class MainWindow : public wxFrame
{
public:
    MainWindow();

public:
    enum { ID_Import = 1, ID_Outport };

private:
    void Init();
    void InitMenu();
    void InitMenuFile(wxMenuBar* menuBar);
    void InitMenuHelp(wxMenuBar* menuBar);
    void InitStatusBar();

    void OnOpen(wxCommandEvent&);
    void OnSave(wxCommandEvent&);
    void OnSaveAs(wxCommandEvent&);
    void OnExit(wxCommandEvent&);

    void OnAbout(wxCommandEvent&);
    void OnClose(wxCloseEvent&);

    void LoadParameters(wxString fileName = wxString());
    void SaveParameters(wxString fileName = wxString());

private:
    std::map<LinkType, Page*> m_pageMap;
    wxStatusBar* m_statusBar;
    wxTimer m_updateTimeTimer;
};
