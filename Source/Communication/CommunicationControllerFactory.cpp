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
    CommunicationType type, wxWindow *parent)
{
    if (type == CommunicationType::SerialPort) {
        return new SerialPortController(parent);
    } else if (type == CommunicationType::UDPClient) {
        return new UDPClientController(parent);
    } else if (type == CommunicationType::UDPServer) {
        return new UDPServerController(parent);
    } else if (type == CommunicationType::TCPClient) {
        return new TCPClientController(parent);
    } else if (type == CommunicationType::TCPServer) {
        return new TCPServerController(parent);
    } else if (type == CommunicationType::WSClient) {
        return new WSClientController(parent);
    } else if (type == CommunicationType::WSServer) {
        return new WSServerController(parent);
    }

    return nullptr;
}
