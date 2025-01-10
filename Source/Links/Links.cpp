/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Links.h"

Links::Links() {}

Links::~Links() {}

bool Links::Open()
{
    return false;
}

void Links::Close() {}

void Links::Write(const wxString &data, TextFormat format)
{
    wxUnusedVar(data);
    wxUnusedVar(format);
}

void Links::Load(const wxJSONValue &parameters)
{
    m_parameters = parameters;
}

wxJSONValue Links::Save()
{
    return m_parameters;
}