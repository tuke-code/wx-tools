/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "PageFactory.h"

#include "LinksUi/LinksControllerFactory.h"

PageFactory::PageFactory() {}

PageFactory &PageFactory::singleton()
{
    static PageFactory instance;
    return instance;
}

Page *PageFactory::CreatePage(LinkType type, wxWindow *parent)
{
    auto *page = new Page(type, parent);
    return page;
}
