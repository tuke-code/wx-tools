/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "LinkUi.h"

#include <wx/event.h>
#include <wx/wx.h>

LinkUi::LinkUi(wxWindow *parent)
    : wxGridBagSizer(4, 4)
    , m_link(nullptr)
{}

LinkUi::~LinkUi()
{
    if (m_link) {
        m_link->Close();
    }
}

Link *LinkUi::GetLink() const
{
    return m_link;
}

bool LinkUi::Open()
{
    m_link = NewLink();
    if (!m_link) {
        return false;
    }

    m_link->Load(Save());
    if (m_link) {
        wxtInfo() << "Link parameters: " << m_link->Save().dump();
    }

    return m_link->Open();
}

void LinkUi::Close()
{
    if (m_link) {
        m_link->Close();
        DeleteLink(m_link);
        m_link = nullptr;
    }
}

bool LinkUi::IsOpen() const
{
    return m_link != nullptr;
}

void LinkUi::Disable() {}

void LinkUi::Enable() {}

wxtJson LinkUi::Save() const
{
    wxtJson json;
    return json;
}

void LinkUi::Load(const wxtJson &json)
{
    wxUnusedVar(json);
}

void LinkUi::Refresh()
{
    // Nothing to do yet...
}

Link *LinkUi::NewLink()
{
    return nullptr;
}

void LinkUi::DeleteLink(Link *link)
{
    wxUnusedVar(link);
}
