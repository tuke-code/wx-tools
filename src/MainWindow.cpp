/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "MainWindow.h"

#include <fmt/format.h>
#include <fstream>
#include <wx/filename.h>
#include <wx/stdpaths.h>

#include "Page/Page.h"

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, fmt::format("wxTools v{}", std::string(WXT_GIT_TAG)))
    , m_statusBar(nullptr)
{
    Init();

#if defined(WIN32)
    wxIcon icon;
    icon.LoadFile("IDI_ICON1", wxBITMAP_TYPE_ICO_RESOURCE);
    SetIcon(icon);
#endif

    m_notebook = new wxNotebook(this, wxID_ANY);
    auto types = GetSuportedLinkTypes();
    for (auto type : types) {
        auto* page = new Page(type, m_notebook);
        if (page != nullptr) {
            m_notebook->AddPage(page, GetLinkName(type));
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
                                _("Open parameters file"),
                                wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Desktop),
                                "wxTools.json",
                                _("JSON files (*.json)|*.json"),
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
                                _("Save parameters file"),
                                wxStandardPaths::Get().GetUserDir(wxStandardPaths::Dir_Desktop),
                                "wxTools.json",
                                _("JSON files (*.json)|*.json"),
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
    wxLogMessage("The application will be closed!", this);
    Close(true);
}

void MainWindow::OnAbout(wxCommandEvent&)
{
    // __DATE__ __TIME__ to wxDateTime
    wxDateTime dt;
    dt.ParseDate(__DATE__);
    wxString d = dt.FormatDate();
    wxDateTime tm;
    tm.ParseTime(__TIME__);
    wxString t = tm.FormatTime();

    wxString info = _("wxTools - A set of tools developed with wxWidgets\n");
    info += "\n";
    info += _("Version: ") + std::string(WXT_GIT_TAG) + std::string("\n");
    info += _("Author: x-tools-author\n");
    info += _("Email: x-tools@outlook.com\n");
    info += "\n";
    info += _("Commit: ") + std::string(WXT_GIT_COMMIT) + std::string("\n");
    info += _("Date: ") + std::string(WXT_GIT_COMMIT_TIME) + std::string("\n");
    info += _("Build: ") + d + wxString(" ") + t + std::string("\n");
    info += std::string("\n");
    info += _("Copyright");
    info += fmt::format(" 2024-{} x-tools-author. ", std::string(__DATE__).substr(7, 4));
    info += _("All rights reserved.\n");
    wxMessageBox(info, _("About wxTools"), wxOK | wxICON_INFORMATION);
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
    menuBar->Append(menuFile, _("File"));

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
    menuBar->Append(menuHelp, _("Help"));

    menuHelp->Append(wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);

    wxMenuItem* item = menuHelp->Append(wxID_HELP);
    item->SetHelp(_("Visit online documentation page."));
    static const wxString helpUrl{"https://x-tools-author.github.io/wx-tools/"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(helpUrl); }, wxID_HELP);

    menuHelp->AppendSeparator();

    wxString help = _("Visit GitHub page to get more information.");
    item = menuHelp->Append(wxID_ANY, _("Get Source from GitHub"), help);
    static const wxString githubUrl{"https://github.com/x-tools-author/wx-tools"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(githubUrl); }, item->GetId());

    help = _("Visit Gitee page to get more information.");
    item = menuHelp->Append(wxID_ANY, _("Get Source from Gitee"), help);
    static const wxString giteeUrl{"https://gitee.com/x-tools-author/wx-tools"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(giteeUrl); }, item->GetId());

    help = _("Visit GitHub home page of author.");
    item = menuHelp->Append(wxID_ANY, _("GitHub Home Page"), help);
    static const wxString githubHomeUrl{"https://github.com/x-tools-author"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(githubHomeUrl); }, item->GetId());

    help = _("Visit Gitee home page of author.");
    item = menuHelp->Append(wxID_ANY, _("Gitee Home Page"), help);
    static const wxString giteeHomeUrl{"https://gitee.com/x-tools-author"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(giteeHomeUrl); }, item->GetId());

#if defined(WIN32)
    menuHelp->AppendSeparator();

    help = _("Visit Microsoft Store page to buy wxTools.");
    item = menuHelp->Append(wxID_ANY, _("Supporting Author"), help);
    static const wxString storeUrl{"https://www.microsoft.com/store/apps/9NX1D0CCV9T7"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(storeUrl); }, item->GetId());

    help = _("Visit Microsoft Store home page of author.");
    item = menuHelp->Append(wxID_ANY, _("Other Applications"), help);
    static wxString storeHomeUrl{"https://apps.microsoft.com/search/publisher?name=x-tools-author"};
    Bind(wxEVT_MENU, [](wxCommandEvent&) { wxLaunchDefaultBrowser(storeHomeUrl); }, item->GetId());
#endif
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
    wxString name = GetLinkRawName(type);
    name.Replace(" ", "");
    return name.ToStdString() + ".json";
}

void MainWindow::LoadParameters(wxString fileName)
{
    if (fileName.IsEmpty()) {
        fileName = GetSettingsFileName();
    }

    if (!wxFileName::Exists(fileName)) {
        return;
    }

    std::ifstream ifs(fileName.ToStdString());
    wxtJson json;
    ifs >> json;

    if (!json.is_object()) {
        return;
    }

    for (auto it = m_pageMap.begin(); it != m_pageMap.end(); ++it) {
        Page* page = it->second;
        wxString name = GetPageParameterFileName(it->first);
        if (!json.contains(name.ToStdString())) {
            continue;
        }

        wxtJson pageJson = json[name.ToStdString()];
        if (pageJson.is_object()) {
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
        fileName = GetSettingsFileName();
    }

    std::ofstream ofs(fileName.ToStdString());
    ofs << wxTools.dump(4);
    ofs.close();
}
