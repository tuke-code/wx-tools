/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationPopup.h"

#include <wx/gbsizer.h>
#include <wx/wx.h>

CommunicationPopup::CommunicationPopup(wxWindow *parent, int flags)
    : wxPopupTransientWindow(parent, flags)
    , m_enableTxMask(nullptr)
    , m_txMask(nullptr)
    , m_refresh(nullptr)
{
    m_enableTxMask = new wxCheckBox(this, wxID_ANY, wxT("Enable Tx Mask"));
    auto rxText = new wxStaticText(this, wxID_ANY, wxT("Rx Mask:"));
    m_txMask = new wxSpinCtrl(this, wxID_ANY);
    m_refresh = new wxButton(this, wxID_ANY, wxT("Refresh"));

    wxGridBagSizer *sizer = new wxGridBagSizer(4, 4);
    sizer->Add(m_enableTxMask, wxGBPosition(0, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    sizer->Add(rxText, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 0);
    sizer->Add(m_txMask, wxGBPosition(1, 1), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(m_refresh, wxGBPosition(2, 0), wxGBSpan(1, 2), wxEXPAND | wxALL, 0);
    sizer->AddGrowableCol(1);
    SetSizerAndFit(sizer);

    m_txMask->SetRange(0, 255);
}
