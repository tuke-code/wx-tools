/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "CommunicationFactory.h"

#include "SerialPort.h"

CommunicationFactory::CommunicationFactory() {}

CommunicationFactory &CommunicationFactory::Singleton()
{
    static CommunicationFactory instance;
    return instance;
}

Communication *CreateCommunication(wxWindow *parent, CommunicationType type)
{
    if (type == CommunicationType::SerialPort) {
        return new SerialPort();
    }
    return nullptr;
}
