/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPServer.h"
#include "UDPServer_p.h"

using asio::ip::udp;

UDPServer::UDPServer()
    : SocketServer(d = new UDPServerPrivate)
{}

UDPServer::~UDPServer()
{
    if (d->socket) {
        d->socket->close();
        delete d->socket;
        d->socket = nullptr;
    }

    delete d;
    d = nullptr;
}

void ReadData(asio::ip::udp::socket *socket, UDPServer *udpServer)
{
    if (!socket || !udpServer) {
        return;
    }

    char buffer[1024 * 1024] = {0};
    size_t receivedBytes = 0;
    while (1) {
        try {
            udp::endpoint senderEndpoint;
            auto asioBuffer = asio::buffer(buffer, sizeof(buffer));
            receivedBytes = socket->receive_from(asioBuffer, senderEndpoint);
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
            udpServer->bytesReadSignal(buffer, ip + ":" + port);
            udpServer->newClientSignal(ip, socket->remote_endpoint().port());
        }
    }
}

bool UDPServer::Open()
{
    Close();

    d->socket = new udp::socket(d->ioContext, udp::endpoint(udp::v4(), 0));
    udp::resolver resolver(d->ioContext);
    std::string ip = std::string(d->serverAddress.mb_str());
    std::string port = std::to_string(d->serverPort);
    auto endpoints = resolver.resolve(udp::v4(), ip, port);
    d->endpoint = *endpoints.begin();

    std::thread t(ReadData, d->socket, this);
    t.detach();

    return true;
}

void UDPServer::Close()
{
    if (d->socket) {
        d->socket->close();
    }
}

void UDPServer::Write(const wxString &data, TextFormat format)
{
    auto msg = data.ToStdString();
    auto buffer = asio::buffer(msg.data(), msg.size());
    auto ret = d->socket->send_to(asio::buffer(msg), d->endpoint);
    if (ret > 0) {
        std::string ip = d->endpoint.address().to_string();
        std::string port = std::to_string(d->endpoint.port());
        bytesWrittenSignal(buffer, ip + ":" + port);
    }
}
