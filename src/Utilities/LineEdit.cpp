/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "LineEdit.h"

LineEdit::LineEdit(wxWindow *parent)
    : wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize)
{
    Bind(wxEVT_TEXT, &LineEdit::OnText, this);
}

void LineEdit::SetTextFormat(TextFormat format)
{
    m_textFormat = format;
}

wxToolsConstBuffer LineEdit::GetBuffer() const
{
    return wxToolsConstBuffer();
}

void LineEdit::OnText(wxCommandEvent &event)
{
    wxUnusedVar(event);
    if (m_textFormat == TextFormat::Bin) {
        SetValue(FormatTextToBinString(GetValue()));
    } else if (m_textFormat == TextFormat::Oct) {
        SetValue(FormatTextToOctString(GetValue()));
    } else if (m_textFormat == TextFormat::Dec) {
        SetValue(FormatTextToDecString(GetValue()));
    } else if (m_textFormat == TextFormat::Hex) {
        SetValue(FormatTextToHexString(GetValue()));
    } else if (m_textFormat == TextFormat::Ascii) {
        SetValue(FormatTextToAsciiString(GetValue()));
    }
}

wxString LineEdit::FormatTextToBinString(const wxString &text)
{
    // 1. remove all spaces on head of the text
    // 2. remove all characters (except '0' and '1')  from the text
    // 3. split the text into 8-bit blocks
    // 4. add a space between each block

    wxString result;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '0' || text[i] == '1') {
            result += text[i];
        }
    }

    wxString temp;
    for (size_t i = 0; i < result.size(); ++i) {
        temp += result[i];
        if ((i + 1) % 8 == 0) {
            temp += ' ';
        }
    }

    return temp;
}

wxString LineEdit::FormatTextToOctString(const wxString &text)
{
    // 1. remove all spaces on head of the text
    // 2. remove all characters (except '0' to '7')  from the text
    // 3. split the text into 3-bit blocks
    // 4. add a space between each block

    wxString result;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] >= '0' && text[i] <= '7') {
            result += text[i];
        }
    }

    wxString temp;
    for (size_t i = 0; i < result.size(); ++i) {
        temp += result[i];
        if ((i + 1) % 3 == 0) {
            temp += ' ';
        }
    }

    return temp;
}

wxString LineEdit::FormatTextToDecString(const wxString &text)
{
    // 1. remove all spaces on head of the text
    // 2. remove all characters (except '0' to '9')  from the text
    // 3. split the text into 3-bit blocks
    // 4. add a space between each block

    wxString result;
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] >= '0' && text[i] <= '9') {
            result += text[i];
        }
    }

    wxString temp;
    for (size_t i = 0; i < result.size(); ++i) {
        temp += result[i];
        if ((i + 1) % 3 == 0) {
            temp += ' ';
        }
    }

    return temp;
}

wxString LineEdit::FormatTextToHexString(const wxString &text)
{
    // 1. remove all spaces on head of the text
    // 2. remove all characters (except '0' to '9', 'a' to 'f', 'A' to 'F')  from the text
    // 3. split the text into 2-bit blocks
    // 4. add a space between each block

    wxString result;
    for (size_t i = 0; i < text.size(); ++i) {
        if ((text[i] >= '0' && text[i] <= '9') || (text[i] >= 'a' && text[i] <= 'f')
            || (text[i] >= 'A' && text[i] <= 'F')) {
            result += text[i];
        }
    }

    wxString temp;
    for (size_t i = 0; i < result.size(); ++i) {
        temp += result[i];
        if ((i + 1) % 2 == 0) {
            temp += ' ';
        }
    }

    return temp;
}

wxString LineEdit::FormatTextToAsciiString(const wxString &text)
{
    // 1. remove all spaces on head of the text
    // 2. remove all characters (except '0' to '9', 'a' to 'z', 'A' to 'Z', ' ', '.', ',', '!', '?', ':', ';', '\'', '"', '(', ')', '[', ']', '{', '}', '<', '>', '+', '-', '*', '/', '=', '_', '&', '^', '%', '$', '#', '@', '~', '`', '|', '\\', '\n', '\r', '\t')  from the text
    // 3. add a space between each character

    wxString result;
    for (size_t i = 0; i < text.size(); ++i) {
        if ((text[i] >= '0' && text[i] <= '9') || (text[i] >= 'a' && text[i] <= 'z')
            || (text[i] >= 'A' && text[i] <= 'Z') || text[i] == ' ' || text[i] == '.'
            || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == ':'
            || text[i] == ';' || text[i] == '\'' || text[i] == '"' || text[i] == '('
            || text[i] == ')' || text[i] == '[' || text[i] == ']' || text[i] == '{'
            || text[i] == '}' || text[i] == '<' || text[i] == '>' || text[i] == '+'
            || text[i] == '-' || text[i] == '*' || text[i] == '/' || text[i] == '='
            || text[i] == '_' || text[i] == '&' || text[i] == '^' || text[i] == '%'
            || text[i] == '$' || text[i] == '#' || text[i] == '@' || text[i] == '~'
            || text[i] == '`' || text[i] == '|' || text[i] == '\\' || text[i] == '\n'
            || text[i] == '\r' || text[i] == '\t') {
            result += text[i];
        }
    }

    wxString temp;
    for (size_t i = 0; i < result.size(); ++i) {
        temp += result[i];
        temp += ' ';
    }

    return temp;
}
