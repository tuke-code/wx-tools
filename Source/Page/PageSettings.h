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

class PageSettingsInput;
class PageSettingsOutput;
class PageSettingsLink;
class PageSettings : public wxBoxSizer
{
public:
    PageSettings(LinkType type, wxWindow *parent);

    PageSettingsInput *GetInputControlBox() const;
    PageSettingsOutput *GetOutputControlBox() const;
    PageSettingsLink *GetCommunicationControlBox() const;

private:
    PageSettingsInput *m_inputControlBox;
    PageSettingsOutput *m_outputControlBox;
    PageSettingsLink *m_communicationControlBox;
};
