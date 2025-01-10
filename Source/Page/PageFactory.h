/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "Common/wxTools.h"
#include "Page.h"

class PageFactory
{
private:
    PageFactory();
    PageFactory(const PageFactory &) = delete;
    PageFactory &operator=(const PageFactory &) = delete;

public:
    static PageFactory &singleton();

    Page *CreatePage(LinkType type, wxWindow *parent);
};
