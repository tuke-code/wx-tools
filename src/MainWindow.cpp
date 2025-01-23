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
    auto types = GetSuportedCommunicationTypes();
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
    wxString info = _("wxTools - A set of tools developed with wxWidgets\n");
    info += _("Version: ") + std::string(WXT_GIT_TAG) + std::string("\n");
    info += _("Author: x-tools-author\n");
    info += _("Email: x-tools@outlook.com\n");
    info += _("Commit: ") + std::string(WXT_GIT_COMMIT) + std::string("\n");
    info += _("Date: ") + std::string(WXT_GIT_COMMIT_TIME) + std::string("\n");
    info += _("Build: ") + fmt::format("{0} {1}", __DATE__, __TIME__) + std::string("\n");
    info += std::string("\n");
    info += wxString::FromUTF8(_("Copyright ©"));
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
#if 1
    InitMenuI18n(menuBar);
#endif
    InitMenuHelp(menuBar);

    SetMenuBar(menuBar);
}

void MainWindow::InitMenuFile(wxMenuBar* menuBar)
{
    wxMenu* menuFile = new wxMenu;
    menuBar->Append(menuFile, _("&File"));

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

void MainWindow::InitMenuI18n(wxMenuBar* menuBar)
{
    wxMenu* menuI18n = new wxMenu;
    menuBar->Append(menuI18n, _("&Language"));

    auto setupItem = [=](const wxString& flag, const wxString& name) {
        wxMenuItem* item = menuI18n->Append(wxID_ANY, name);
        item->SetCheckable(true);
        int id = item->GetId();
        Bind(
            wxEVT_MENU,
            [=](wxCommandEvent&) {
                OnLanguageChanged(flag);
                wxMenu* menu = item->GetMenu();
                for (size_t i = 0; i < menu->GetMenuItemCount(); ++i) {
                    wxMenuItem* item = menu->FindItemByPosition(i);
                    if (item->IsCheckable() && item->GetId() != id) {
                        item->Check(false);
                    }
                }
                item->Check(true);
            },
            id);
    };

    setupItem(wxString("en_US"), wxString("English"));
    setupItem(wxString("zh_CN"), wxString::FromUTF8("简体中文"));
    setupItem(wxString("zh_TW"), wxString::FromUTF8("繁体中文"));
    setupItem(wxString("ar"), wxString::FromUTF8("العربية"));
    setupItem(wxString("cs"), wxString::FromUTF8("Čeština"));
    setupItem(wxString("da"), wxString::FromUTF8("Dansk"));
    setupItem(wxString("de"), wxString::FromUTF8("Deutsch"));
    setupItem(wxString("es"), wxString::FromUTF8("Español"));
    setupItem(wxString("fa"), wxString::FromUTF8("فارسی"));
    setupItem(wxString("fi"), wxString::FromUTF8("Suomi"));
    setupItem(wxString("fr"), wxString::FromUTF8("Français"));
    setupItem(wxString("he"), wxString::FromUTF8("עִבְרִית"));
    setupItem(wxString("uk"), wxString::FromUTF8("українська мова"));
    setupItem(wxString("it"), wxString::FromUTF8("Italiano"));
    setupItem(wxString("ja"), wxString::FromUTF8("日本语"));
    setupItem(wxString("ko"), wxString::FromUTF8("한글"));
    setupItem(wxString("lt"), wxString::FromUTF8("Lietuvių kalba"));
    setupItem(wxString("pl"), wxString::FromUTF8("Polski"));
    setupItem(wxString("pt"), wxString::FromUTF8("Português"));
    setupItem(wxString("ru"), wxString::FromUTF8("русский язык"));
    setupItem(wxString("sk"), wxString::FromUTF8("Slovenčina"));
    setupItem(wxString("sl"), wxString::FromUTF8("Slovenščina"));
    setupItem(wxString("sv"), wxString::FromUTF8("Svenska"));
}

void MainWindow::InitMenuHelp(wxMenuBar* menuBar)
{
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    menuBar->Append(menuHelp, _("&Help"));

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
    wxString name = GetLinkName(type);
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

void MainWindow::OnLanguageChanged(const wxString& flag)
{
    int ret = wxMessageBox(_("Reboot the application to make the language effectived, reboot now?"),
                           _("Need to Reboot"),
                           wxYES_NO | wxICON_QUESTION);
    if (ret == wxNO) {
        return;
    }

    wxExecute(wxStandardPaths::Get().GetExecutablePath());
    this->Close(true);
}
