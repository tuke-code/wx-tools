/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPServer.h"

using asio::ip::udp;

UDPServer::UDPServer() {}

UDPServer::~UDPServer() {}

void ReadData(asio::ip::udp::socket *socket, UDPServer *UDPServer)
{
    if (!socket || !UDPServer) {
        return;
    }

    char buffer[1024] = {0};
    size_t receivedBytes = 0;
    while (1) {
        try {
            udp::endpoint senderEndpoint;
            receivedBytes = socket->receive_from(asio::buffer(buffer, 1024), senderEndpoint);
        } catch (asio::system_error &e) {
            std::string errorString = e.what();
            wxString msg = wxString::Format("Read data failed, error message: %s", errorString);
            wxToolsInfo() << msg;
            break;
        }

        if (receivedBytes > 0) {
            std::string data(buffer, receivedBytes);
            asio::const_buffer buffer(data.data(), data.size());
            std::string ip = socket->remote_endpoint().address().to_string();
            std::string port = std::to_string(socket->remote_endpoint().port());
            UDPServer->bytesReadSignal(buffer, ip + ":" + port);
        }
    }

    delete socket;
}

bool UDPServer::Open()
{
    Close();

    m_socket = new udp::socket(m_ioContext, udp::endpoint(udp::v4(), 0));
    udp::resolver resolver(m_ioContext);
    std::string ip = std::string(m_serverAddress.mb_str());
    std::string port = std::to_string(m_serverPort);
    auto endpoints = resolver.resolve(udp::v4(), ip, port);
    m_endpoint = *endpoints.begin();

    std::thread t(ReadData, m_socket, this);
    t.detach();

    return true;
}

void UDPServer::Close()
{
    m_socket->close();
    delete m_socket;
    m_socket = nullptr;
}

void UDPServer::Write(const wxString &data, TextFormat format)
{
    auto msg = data.ToStdString();
    auto buffer = asio::buffer(msg.data(), msg.size());
    auto ret = m_socket->send_to(asio::buffer(msg), m_endpoint);
    if (ret > 0) {
        bytesWrittenSignal(buffer, "127.0.0.1");
    }
}