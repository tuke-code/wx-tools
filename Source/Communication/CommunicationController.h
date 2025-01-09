/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <wx/gbsizer.h>
#include <wx/jsonreader.h>
#include <wx/jsonval.h>
#include <wx/wx.h>

#include "Communication.h"

class CommunicationController : public wxGridBagSizer
{
public:
    CommunicationController(wxWindow *parent = nullptr);
    ~CommunicationController();
    Communication *GetCommunication() const;

    bool Open();
    void Close();
    bool IsOpen() const;

    virtual void Disable();
    virtual void Enable();
    virtual wxJSONValue Save() const;
    virtual void Load(const wxJSONValue &json);

protected:
    virtual Communication *CreateCommunication();
    virtual void AboutToOpen(Communication *communication);
    virtual void AboutToClose(Communication *communication);

private:
    Communication *m_communication;
};
