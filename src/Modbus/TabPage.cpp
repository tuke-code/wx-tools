/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TabPage.h"

#include "TabPageRegisters.h"
#include "TabPageRxTx.h"

namespace Modbus {

TabPage::TabPage(wxWindow *parent)
    : wxNotebook(parent, wxID_ANY)
{
    AddPage(new TabPageRxTx(this), _("RxTx Data"));
    AddPage(new TabPageRegisters(this), _("Coils"));
    AddPage(new TabPageRegisters(this), _("Discrete Inputs"));
    AddPage(new TabPageRegisters(this), _("Input Registers"));
    AddPage(new TabPageRegisters(this), _("Holding Registers"));
}

TabPage::~TabPage() {}

} // namespace Modbus
