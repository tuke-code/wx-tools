/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/notebook.h>
#include <wx/wx.h>

namespace Modbus {

class TabPage : public wxNotebook
{
public:
    TabPage(wxWindow *parent);
    ~TabPage();
};

} // namespace Modbus
