/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "MainWindow.h"

#include <fstream>

#include <wx/filename.h>
#include <wx/jsonreader.h>
#include <wx/jsonval.h>
#include <wx/notebook.h>

#include "Common/wxTools.h"
#include "Page/PageFactory.h"

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "wxTools")
    , m_statusBar(nullptr)
{
    Init();

    auto* notebook = new wxNotebook(this, wxID_ANY);
    auto types = GetSuportedCommunicationTypes();
    for (auto type : types) {
        auto* page = PageFactory::singleton().CreatePage(type, notebook);
        if (page != nullptr) {
            notebook->AddPage(page, GetCommunicationName(type));
            m_pageMap[type] = page;
        } else {
            int cookedType = static_cast<int>(type);
            wxToolsLog(ERROR) << wxString::Format("Create page failed, type: %d", cookedType);
        }
    }

    LoadParameters();

    auto const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(notebook, 1, wxEXPAND | wxALL, 0);
    SetSizerAndFit(sizer);

    SetSize(wxSize(1024, 600));
    Centre();

    Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this, GetId());
    m_updateTimeTimer.Bind(wxEVT_TIMER, &MainWindow::OnTimer, this);
}

void MainWindow::OnExit(wxCommandEvent& event)
{
    wxLogMessage("The application will be closed!");
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World",
                 wxOK | wxICON_INFORMATION);
}

void MainWindow::OnClose(wxCloseEvent& event)
{
    SaveParameters();
    Destroy();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
    m_statusBar->SetStatusText(wxDateTime::Now().FormatTime(), 1);
}

void MainWindow::Init()
{
    InitMenu();
    InitStatusBar();
}

void MainWindow::InitMenu()
{
    wxMenuBar* menuBar = new wxMenuBar;
    InitMenuFile(menuBar);
    InitMenuHelp(menuBar);

    SetMenuBar(menuBar);
}

void MainWindow::InitMenuFile(wxMenuBar* menuBar)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello,
                     "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    menuBar->Append(menuFile, _("&File"));

    Bind(wxEVT_MENU, &MainWindow::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

void MainWindow::InitMenuHelp(wxMenuBar* menuBar)
{
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    menuBar->Append(menuHelp, "&Help");

    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
}

void MainWindow::InitStatusBar()
{
    m_statusBar = CreateStatusBar(2);
    int widths[] = {-1, 60};
    SetStatusWidths(2, widths);

    m_updateTimeTimer.Start(1000);
}

void MainWindow::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

std::string GetPageParameterFileName(CommunicationType type)
{
    wxString name = GetCommunicationName(type);
    name.Replace(" ", "");
    return name.ToStdString() + ".json";
}

void MainWindow::LoadParameters()
{
    for (auto it = m_pageMap.begin(); it != m_pageMap.end(); ++it) {
        auto* page = it->second;
        wxString name = GetPageParameterFileName(it->first);
        if (!wxFileName::Exists(name)) {
            continue;
        }

        wxJSONReader jsonReader;
        wxJSONValue json;
        jsonReader.Parse(name, &json);

        if (it->first == CommunicationType::SerialPort) {
            page->LoadParameters(json);
        }
    }
}

void MainWindow::SaveParameters()
{
    for (auto it = m_pageMap.begin(); it != m_pageMap.end(); ++it) {
        auto* page = it->second;
        auto json = page->SaveParameters();
        wxString name = GetPageParameterFileName(it->first);
        std::ofstream file(name.ToStdString());
        file << json.AsString();
    }
}
