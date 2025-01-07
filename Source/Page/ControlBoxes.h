/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
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

class InputControlBox;
class OutputControlBox;
class CommunicationControlBox;
class ControlBoxes : public wxBoxSizer
{
public:
    ControlBoxes(CommunicationType type, wxWindow *parent);

    InputControlBox *GetInputControlBox() const;
    OutputControlBox *GetOutputControlBox() const;
    CommunicationControlBox *GetCommunicationControlBox() const;

private:
    InputControlBox *m_inputControlBox;
    OutputControlBox *m_outputControlBox;
    CommunicationControlBox *m_communicationControlBox;
};
