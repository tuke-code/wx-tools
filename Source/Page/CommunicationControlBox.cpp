/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationControlBox.h"

#include <wx/gbsizer.h>

#include "Communication/CommunicationController.h"
#include "Communication/CommunicationControllerFactory.h"
#include "Communication/SerialPortController.h"

CommunicationControlBox::CommunicationControlBox(CommunicationType type, wxWindow *parent)
    : wxStaticBoxSizer(wxVERTICAL, parent, wxT("Communication Control"))
{
    auto *sizer = new wxGridBagSizer(4, 4);
    Add(sizer, 1, wxEXPAND | wxALL, 0);

    auto settingsButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Settings"));
    auto sendingButton = new wxButton(GetStaticBox(), wxID_ANY, wxT("Send"));
    auto buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    buttonSizer->Add(settingsButton, 1, wxEXPAND | wxALL, 0);
    buttonSizer->Add(sendingButton, 1, wxEXPAND | wxALL, 0);

    auto &factory = CommunicationControllerFactory::singleton();
    auto *controller = factory.CreateCommunicationController(type, GetStaticBox());

    sizer->Add(controller, wxGBPosition(0, 0), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
    sizer->Add(buttonSizer, wxGBPosition(1, 0), wxGBSpan(1, 1), wxEXPAND | wxALL, 0);
}
