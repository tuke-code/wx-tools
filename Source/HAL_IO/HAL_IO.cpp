/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "HAL_IO.h"

HAL_IO::HAL_IO() {}

HAL_IO::~HAL_IO() {}

bool HAL_IO::Open()
{
    return false;
}

void HAL_IO::Close() {}

void HAL_IO::Write(const wxString &data, TextFormat format)
{
    wxUnusedVar(data);
    wxUnusedVar(format);
}

void HAL_IO::Load(const wxJSONValue &parameters)
{
    m_parameters = parameters;
}

wxJSONValue HAL_IO::Save()
{
    return m_parameters;
}