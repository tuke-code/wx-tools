/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Link.h"

Link::Link() {}

Link::~Link() {}

bool Link::Open()
{
    return false;
}

void Link::Close() {}

void Link::Write(const wxString &data, TextFormat format)
{
    wxUnusedVar(data);
    wxUnusedVar(format);
}

void Link::Load(const nlohmann::json &parameters)
{
    m_parameters = parameters;
}

nlohmann::json Link::Save()
{
    return m_parameters;
}
