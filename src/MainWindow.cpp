/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "MainWindow.h"

#include <fstream>

#include <wx/filename.h>
#include <wx/stdpaths.h>

#include "Page/Page.h"

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "wxTools")
    , m_statusBar(nullptr)
{
    Init();

    m_notebook = new wxNotebook(this, wxID_ANY);
    auto types = GetSuportedCommunicationTypes();
    for (auto type : types) {
        auto* page = new Page(type, m_notebook);
        if (page != nullptr) {
            m_notebook->AddPage(page, GetCommunicationName(type));
            m_pageMap[type] = page;
        } else {
            int cookedType = static_cast<int>(type);
            wxtLog(ERROR) << wxString::Format("Create page failed, type: %d", cookedType);
        }
    }

    m_updateTimeTimer.Bind(wxEVT_TIMER, [this](wxTimerEvent&) {
        this->m_statusBar->SetStatusText(wxDateTime::Now().FormatTime(), 1);
    });

    LoadParameters();

    auto const sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_notebook, 1, wxEXPAND | wxALL, 0);
    SetSizerAndFit(sizer);

    SetSize(wxSize(1024, 600));
    Centre();
}

MainWindow::~MainWindow()
{
    SaveParameters();
}

void MainWindow::OnOpen(wxCommandEvent&)
{
    wxFileDialog openFileDialog(this,
                                wxT("Open parameters file"),
                                wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Desktop),
                                "wxTools.json",
                                "JSON files (*.json)|*.json",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    openFileDialog.ShowModal();
    wxString fileName = openFileDialog.GetPath();
    LoadParameters(fileName);
}

void MainWindow::OnSave(wxCommandEvent&)
{
    SaveParameters();
}

void MainWindow::OnSaveAs(wxCommandEvent&)
{
    wxFileDialog saveFileDialog(this,
                                wxT("Save parameters file"),
                                wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Desktop),
                                "wxTools.json",
                                "JSON files (*.json)|*.json",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    saveFileDialog.ShowModal();
    wxString fileName = saveFileDialog.GetPath();
    wxtInfo() << fileName;
    SaveParameters(fileName);
}

void MainWindow::OnNew(wxCommandEvent&)
{
    wxExecute(wxStandardPaths::Get().GetExecutablePath());
}

void MainWindow::OnExit(wxCommandEvent&)
{
    wxLogMessage("The application will be closed!");
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent&)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World",
                 wxOK | wxICON_INFORMATION);
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
    menuBar->Append(menuFile, wxT("&File"));

    menuFile->Append(wxID_NEW);
    menuFile->Append(wxID_OPEN);
    menuFile->Append(wxID_SAVE);
    menuFile->Append(wxID_SAVEAS);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    Bind(wxEVT_MENU, &MainWindow::OnNew, this, wxID_NEW);
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainWindow::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainWindow::OnSaveAs, this, wxID_SAVEAS);
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

std::string GetPageParameterFileName(LinkType type)
{
    wxString name = GetCommunicationName(type);
    name.Replace(" ", "");
    return name.ToStdString() + ".json";
}

void MainWindow::LoadParameters(wxString fileName)
{
    if (fileName.IsEmpty()) {
        fileName = wxToolsGetSettingsFileName();
    }

    if (!wxFileName::Exists(fileName)) {
        return;
    }

    std::ifstream ifs(fileName.ToStdString());
    wxtJson json;
    ifs >> json;

    for (auto it = m_pageMap.begin(); it != m_pageMap.end(); ++it) {
        Page* page = it->second;
        wxString name = GetPageParameterFileName(it->first);
        wxtJson pageJson = json[name.ToStdString()];
        if (!pageJson.is_null()) {
            page->Load(pageJson);
        }
    }

    wxtJson tabIndexJson = json["tabIndex"];
    if (!tabIndexJson.is_null()) {
        int tabIndex = tabIndexJson.get<int>();
        if (tabIndex >= 0 || tabIndex < m_notebook->GetPageCount()) {
            m_notebook->SetSelection(tabIndex);
        }
    }
}

void MainWindow::SaveParameters(wxString fileName)
{
    wxtJson wxTools = wxtJson::object();
    wxTools["tabIndex"] = m_notebook->GetSelection();

    for (auto it = m_pageMap.begin(); it != m_pageMap.end(); ++it) {
        Page* page = it->second;
        wxtJson json = page->Save();
        wxString name = GetPageParameterFileName(it->first);
        wxTools[name.ToStdString()] = json;
    }

    // Write json to file
    if (fileName.IsEmpty()) {
        fileName = wxToolsGetSettingsFileName();
    }

    std::ofstream ofs(fileName.ToStdString());
    ofs << wxTools.dump(4);
    ofs.close();
}
