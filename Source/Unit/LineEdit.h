/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/textctrl.h>
#include <wx/wx.h>

#include "Common/eTools.h"

class LineEdit : public wxTextCtrl
{
public:
    LineEdit(wxWindow *parent);

    void SetTextFormat(TextFormat format);
    wxToolsConstBuffer GetBuffer() const;

private:
    TextFormat m_textFormat;

private:
    void OnText(wxCommandEvent &event);

    wxString FormatTextToBinString(const wxString &text);
    wxString FormatTextToOctString(const wxString &text);
    wxString FormatTextToDecString(const wxString &text);
    wxString FormatTextToHexString(const wxString &text);
    wxString FormatTextToAsciiString(const wxString &text);
};