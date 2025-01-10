/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/wx.h>

#include "Common/wxTools.h"

class LinksController;
class LinksControllerFactory
{
private:
    LinksControllerFactory();
    LinksControllerFactory(const LinksControllerFactory &) = delete;
    LinksControllerFactory &operator=(const LinksControllerFactory &) = delete;

public:
    static LinksControllerFactory &singleton();
    LinksController *CreateCommunicationController(LinkType type, wxWindow *parent);
};
