/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <sigslot/signal.hpp>
#include <wx/wx.h>

#include "Common/wxTools.h"

class ControlPanelInput;
class ControlPanelOutput;
class ControlPanelLink;
class ControlPanel : public wxBoxSizer
{
public:
    ControlPanel(LinkType type, wxWindow *parent);

    ControlPanelInput *GetInputControlBox() const;
    ControlPanelOutput *GetOutputControlBox() const;
    ControlPanelLink *GetCommunicationControlBox() const;

private:
    ControlPanelInput *m_inputControlBox;
    ControlPanelOutput *m_outputControlBox;
    ControlPanelLink *m_communicationControlBox;
};
