/***************************************************************************************************
 * 版权声明 © 2024 声菲特. 保留所有版权。
 **************************************************************************************************/
#include "LinksControllerFactory.h"

#include "SerialPortController.h"
#include "TCPClientController.h"
#include "TCPServerController.h"
#include "UDPClientController.h"
#include "UDPServerController.h"
#include "WSClientController.h"
#include "WSServerController.h"

LinksControllerFactory::LinksControllerFactory() {}

LinksControllerFactory &LinksControllerFactory::singleton()
{
    static LinksControllerFactory instance;
    return instance;
}

LinksController *LinksControllerFactory::CreateCommunicationController(
    LinkType type, wxWindow *parent)
{
    if (type == LinkType::SerialPort) {
        return new SerialPortController(parent);
    } else if (type == LinkType::UDPClient) {
        return new UDPClientController(parent);
    } else if (type == LinkType::UDPServer) {
        return new UDPServerController(parent);
    } else if (type == LinkType::TCPClient) {
        return new TCPClientController(parent);
    } else if (type == LinkType::TCPServer) {
        return new TCPServerController(parent);
    } else if (type == LinkType::WSClient) {
        return new WSClientController(parent);
    } else if (type == LinkType::WSServer) {
        return new WSServerController(parent);
    }

    return nullptr;
}
