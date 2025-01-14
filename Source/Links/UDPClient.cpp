﻿/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "UDPClient.h"
#include "UDPClient_p.h"

using asio::ip::udp;

UDPClient::UDPClient()
    : SocketClient(d = new UDPClientPrivate)
{}

UDPClient::~UDPClient()
{
    if (d->socket) {
        d->socket->close();
        delete d->socket;
        d->socket = nullptr;
    }

    delete d;
    d = nullptr;
}

void ReadData(UDPClientPrivate *d, UDPClient *udpClient)
{
#if 0
    if (!socket || !udpClient) {
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
            udpClient->bytesReadSignal(buffer, ip + ":" + port);
        }
    }
#endif
    const int maxLength = 1024 * 1024;
    char data[maxLength];
    asio::io_context ioContext;
    udp::endpoint senderEndpoint;
    asio::ip::udp::socket socket(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
    socket.async_receive_from(asio::buffer(data, maxLength),
                              senderEndpoint,
                              [](std::error_code ec, std::size_t bytes_recvd) {
                                  if (!ec && bytes_recvd > 0) {
                                      //
                                  } else {
                                      //
                                  }
                              });
}

bool UDPClient::Open()
{
    Close();

    d->socket = new udp::socket(d->ioContext, udp::endpoint(udp::v4(), 0));
    d->ioContext.run();

    //std::thread t(ReadData, d->socket, this);
    //t.detach();

    return true;
}

void UDPClient::Close()
{
    if (d->socket) {
        d->socket->close();
    }
}

void UDPClient::Write(const wxString &data, TextFormat format)
{
    auto msg = data.ToStdString();
    auto buffer = asio::buffer(msg.data(), msg.size());
    auto ret = d->socket->send_to(asio::buffer(msg), d->endpoint);
    if (ret > 0) {
        bytesWrittenSignal(buffer, "127.0.0.1");
    }
}
