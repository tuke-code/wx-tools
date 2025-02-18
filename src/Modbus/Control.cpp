/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "Control.h"

#include "ControlLink.h"
#include "ControlOther.h"
#include "ControlRtu.h"
#include "ControlTcp.h"

namespace Modbus {

Control::Control(bool isMaster, wxWindow *parent)
    : wxBoxSizer(wxVERTICAL)
{
    ControlLink *linkControl = new ControlLink(parent);
    Add(linkControl, 0, wxEXPAND | wxALL);

    ControlRtu *rtuControl = new ControlRtu(parent);
    Add(rtuControl, 0, wxEXPAND | wxALL);

    ControlTcp *tcpControl = new ControlTcp(parent);
    Add(tcpControl, 0, wxEXPAND | wxALL);

    ControlOther *otherControl = new ControlOther(parent);
    Add(otherControl, 0, wxEXPAND | wxALL);
}

Control::~Control() {}

} // namespace Modbus
