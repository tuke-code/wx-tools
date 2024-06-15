/***************************************************************************************************
 * Copyright 2024 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include "Common/DataStructure.h"

class Communication;
class CommunicationFactory
{
private:
    CommunicationFactory();
    CommunicationFactory(const CommunicationFactory &) = delete;
    CommunicationFactory &operator=(const CommunicationFactory &) = delete;

public:
    static CommunicationFactory &Singleton();
    Communication *CreateCommunication(CommunicationType type);
};
