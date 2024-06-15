/***************************************************************************************************
 * 版权声明 © 2024 声菲特. 保留所有版权。
 **************************************************************************************************/
#include "CommunicationControllerFactory.h"

#include "SerialPortController.h"
#include "TCPClientController.h"
#include "TCPServerController.h"
#include "UDPClientController.h"
#include "UDPServerController.h"
#include "WSClientController.h"
#include "WSServerController.h"

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
    } else if (type == CommunicationType::UDPClient) {
        return new UDPClientController();
    } else if (type == CommunicationType::UDPServer) {
        return new UDPServerController();
    } else if (type == CommunicationType::TCPClient) {
        return new TCPClientController();
    } else if (type == CommunicationType::TCPServer) {
        return new TCPServerController();
    } else if (type == CommunicationType::WSClient) {
        return new WSClientController();
    } else if (type == CommunicationType::WSServer) {
        return new WSServerController();
    }

    return nullptr;
}
