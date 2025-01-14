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
    enum { ID_Hello = 1 };

private:
    void Init();
    void InitMenu();
    void InitMenuFile(wxMenuBar* menuBar);
    void InitMenuHelp(wxMenuBar* menuBar);
    void InitStatusBar();

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    void OnTimer(wxTimerEvent& event);

    void LoadParameters();
    void SaveParameters();

private:
    std::map<LinkType, Page*> m_pageMap;
    wxStatusBar* m_statusBar;
    wxTimer m_updateTimeTimer;
};
