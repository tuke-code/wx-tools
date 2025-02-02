/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "LineEdit.h"

class BinTextValidator : public wxTextValidator
{
public:
    BinTextValidator()
        : wxTextValidator(wxFILTER_XDIGITS) {};

    wxString IsValid(const wxString &str) const override
    {
        wxtInfo() << "123";
        return "123";
    }
};

LineEdit::LineEdit(wxWindow *parent)
    : wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize)
{
    
}

void LineEdit::SetTextFormat(TextFormat format)
{
    if (format == TextFormat::Bin) {
        SetValidator(BinTextValidator());
    } else if (format == TextFormat::Oct) {
    } else if (format == TextFormat::Dec) {
    } else if (format == TextFormat::Hex) {
    } else if (format == TextFormat::Ascii) {
        SetValidator(wxTextValidator(wxFILTER_ASCII));
    } else {
        SetValidator(wxTextValidator(wxFILTER_NONE));
    }
}
