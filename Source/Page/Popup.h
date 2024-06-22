﻿/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/popupwin.h>
#include <wx/wx.h>

class Popup : public wxPopupTransientWindow
{
public:
    Popup(wxButton *controlButton, bool showOnBottom = true);

protected:
    bool ProcessLeftDown(wxMouseEvent &event) override;

private:
    wxButton *m_controlButton;
    bool m_showOnBottom;

private:
    void OnControlButtonClicked(wxMouseEvent &event);
};