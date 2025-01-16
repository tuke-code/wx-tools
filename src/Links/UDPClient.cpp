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

UDPClient::UDPClient()
    : SocketClient(d = new UDPClientPrivate)
{}

UDPClient::~UDPClient()
{
    delete d;
    d = nullptr;
}

void ReadData(UDPClientPrivate *d, UDPClient *udpClient)
{
    using asio::ip::udp;
    asio::io_context ioContext;
    udp::socket socket(ioContext, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(ioContext);
    std::string host = d->serverAddress.ToStdString();
    std::string port = std::to_string(d->serverPort);
    auto endpoints = resolver.resolve(udp::v4(), host, port);

    d->invokeCloseSignal.connect([&]() { socket.close(); });
    d->invokeWriteSignal.connect([&](wxString msg, TextFormat) {
        try {
            asio::const_buffer buffer(msg.data(), msg.size());
            size_t len = socket.send_to(buffer, *endpoints.begin());
            if (len > 0) {
                udpClient->bytesWrittenSignal(buffer, d->serverAddress);
            } else {
                wxToolsInfo() << "Write data failed...";
            }
        } catch (asio::system_error &e) {
            wxToolsInfo() << e.what() << e.code();
        }
    });

    while (1) {
        char buffer[10240] = {0};
        udp::endpoint sender;
        try {
            size_t len = socket.receive_from(asio::buffer(buffer, 10240), sender);
            if (len <= 0) {
                continue;
            }

            std::string data(buffer, len);
            asio::const_buffer buffer(data.data(), data.size());
            udpClient->bytesReadSignal(buffer, d->serverAddress);
        } catch (asio::system_error &e) {
            if (e.code().value() != 10004) {
                wxToolsInfo() << e.what();
            }

            break;
        }
    }
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
    d->invokeCloseSignal();
}

void UDPClient::Write(const wxString &data, TextFormat format)
{
    d->invokeWriteSignal(data, format);
}
