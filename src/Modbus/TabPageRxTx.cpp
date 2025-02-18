/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TabPageRxTx.h"

namespace Modbus {

TabPageRxTx::TabPageRxTx(wxWindow *parent)
    : wxTextCtrl(parent,
                 wxID_ANY,
                 wxEmptyString,
                 wxDefaultPosition,
                 wxDefaultSize,
                 wxTE_MULTILINE | wxTE_DONTWRAP)
{}

TabPageRxTx::~TabPageRxTx() {}

} // namespace Modbus
