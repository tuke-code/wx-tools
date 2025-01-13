/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "LinksController.h"

#include <wx/event.h>
#include <wx/wx.h>

LinksController::LinksController(wxWindow *parent)
    : wxGridBagSizer(4, 4)
    , m_link(nullptr)
{}

LinksController::~LinksController() {}

Link *LinksController::GetLink() const
{
    return m_link;
}

bool LinksController::Open()
{
    m_link = CreateLink();
    if (!m_link) {
        return false;
    }

    AboutToOpen(m_link);

    return m_link->Open();
}

void LinksController::Close()
{
    if (m_link) {
        AboutToClose(m_link);

        m_link->Close();
        delete m_link;
        m_link = nullptr;
    }
}

bool LinksController::IsOpen() const
{
    return m_link != nullptr;
}

void LinksController::Disable() {}

void LinksController::Enable() {}

nlohmann::json LinksController::Save() const
{
    nlohmann::json json;
    return json;
}

void LinksController::Load(const nlohmann::json &json)
{
    wxUnusedVar(json);
}

Link *LinksController::CreateLink()
{
    return nullptr;
}

void LinksController::AboutToOpen(Link *link)
{
    link->Load(Save());
}

void LinksController::AboutToClose(Link *link)
{
    wxUnusedVar(link);
    // Nothing to do
}
