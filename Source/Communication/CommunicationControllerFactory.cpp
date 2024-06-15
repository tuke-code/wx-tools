/***************************************************************************************************
 * 版权声明 © 2024 声菲特. 保留所有版权。
 **************************************************************************************************/
#include "CommunicationControllerFactory.h"

#include "SerialPortController.h"

CommunicationControllerFactory::CommunicationControllerFactory() {}

CommunicationControllerFactory &CommunicationControllerFactory::singleton()
{
    static CommunicationControllerFactory instance;
    return instance;
}

CommunicationController *CommunicationControllerFactory::CreateCommunicationController(
    CommunicationType type)
{
    if (type == CommunicationType::SerialPort) {
        return new SerialPortController();
    }

    return nullptr;
}
