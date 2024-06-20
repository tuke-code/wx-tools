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

CommunicationPopup::CommunicationPopup(wxWindow *parent, int flags) : wxPopupWindow(parent, flags)
{
    wxGridBagSizer *sizer = new wxGridBagSizer(4, 4);
    SetSizerAndFit(sizer);
    SetMinSize(wxSize(200, 100));
    SetSize(wxSize(200, 100));

    sizer->Add(new wxStaticText(this, wxID_ANY, "Rx Mask:"), wxGBPosition(0, 0));
}
