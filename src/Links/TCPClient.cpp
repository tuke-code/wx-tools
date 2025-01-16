/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPClient.h"
#include "TCPClient_p.h"

using asio::ip::tcp;

TCPClient::TCPClient()
    : SocketClient(d = new TCPClientPrivate)
{}

TCPClient::~TCPClient()
{
    delete d;
    d = nullptr;
}

void Run(TCPClientPrivate *d, TCPClient *tcpClient)
{
    asio::io_context context;
    tcp::socket socket(context);
    tcp::resolver resolver(context);
    std::string ip = d->serverAddress.ToStdString();
    std::string port = std::to_string(d->serverPort);
    try {
        asio::connect(socket, resolver.resolve(ip, port));
    } catch (const asio::system_error &e) {
        wxToolsWarning() << "Connect to server failed: " << e.what();
        return;
    }

    char rxData[10240] = {0};
    tcp::endpoint sender;
    asio::const_buffer buffer(rxData, 1024);
    socket.async_read_some(buffer, [](std::error_code e, std::size_t len) {

    });
}

bool TCPClient::Open()
{
    std::thread t(Run, d, this);
    t.detach();

    return true;
}

void TCPClient::Close() {}

void TCPClient::Write(const wxString &data, TextFormat format) {}
