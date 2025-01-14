/***************************************************************************************************
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
    asio::io_context ioContext;
    udp::socket socket(ioContext, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(ioContext);
    udp::resolver::results_type endpoints = resolver.resolve(udp::v4(),
                                                             d->serverAddress.ToStdString(),
                                                             std::to_string(d->serverPort));

    const int maxLangth = 1024 * 1024;
    char request[maxLangth];
    //socket.send_to(asio::buffer(request, request_length), *endpoints.begin());

    char reply[maxLangth];
    udp::endpoint senderEndpoint;
    size_t bytesLength = socket.receive_from(asio::buffer(reply, maxLangth), senderEndpoint);
}

bool UDPClient::Open()
{
    Close();

    std::thread t(ReadData, d, this);
    t.detach();

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
