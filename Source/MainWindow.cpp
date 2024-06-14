/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "MainWindow.h"
#include "Page/Page.h"

#include <wx/notebook.h>

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Hello World")
{
    Init();

    auto* notebook = new wxNotebook(this, wxID_ANY);

    auto* page1 = new Page(notebook, wxID_ANY);
#ifdef __WXMSW__
    notebook->AddPage(page1, _("COM"));
#else
    notebook->AddPage(page1, _("TTY"));
#endif

    auto* page2 = new Page(notebook, wxID_ANY);
    notebook->AddPage(page2, _("UDP-C"));
    auto* page3 = new Page(notebook, wxID_ANY);
    notebook->AddPage(page3, _("UDP-S"));

    auto* page4 = new Page(notebook, wxID_ANY);
    notebook->AddPage(page4, _("TCP-C"));
    auto* page5 = new Page(notebook, wxID_ANY);
    notebook->AddPage(page5, _("TCP-S"));

    auto* page6 = new Page(notebook, wxID_ANY);
    notebook->AddPage(page6, _("WS-C"));
    auto* page7 = new Page(notebook, wxID_ANY);
    notebook->AddPage(page7, _("WS-S"));

    notebook->AddPage(new wxTextCtrl(notebook,
                                     wxID_ANY,
                                     "This is a text control",
                                     wxDefaultPosition,
                                     wxDefaultSize,
                                     wxTE_MULTILINE),
                      _("Log"));

    auto const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(notebook, 1, wxEXPAND | wxALL, 0);
    SetSizerAndFit(sizer);

    wxFrame::CreateStatusBar();
    wxFrame::SetStatusText("Welcome to wxWidgets!");
    Centre();
    wxFrame::SetMinSize(wxSize(1024, 600));
    Centre();
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

void MainWindow::Init()
{
    InitMenu();
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

void MainWindow::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}