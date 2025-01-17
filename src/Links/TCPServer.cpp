/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "TCPServer.h"
#include "TCPServer_p.h"

using asio::ip::tcp;

TCPServer::TCPServer()
    : SocketServer(d = new TCPServerPrivate)
{}

TCPServer::~TCPServer()
{
    Close();

    delete d;
    d = nullptr;
}

void SetUpSocket(TCPServerPrivate *d, TCPServer *tcpServer, tcp::socket socket)
{
    d->invokeWriteSignal.connect([=, &socket](const std::string &data, int format) {
        auto bytes = DoEncodeText(data, static_cast<TextFormat>(format));
        bool errorOccurred = false;
        try {
            size_t ret = socket.write_some(bytes);
            if (ret != bytes.size()) {
                errorOccurred = true;
            } else {
                tcpServer->bytesTxSignal(bytes, d->serverAddress);
            }

        } catch (asio::system_error error) {
            errorOccurred = true;
        }

        if (errorOccurred) {
            std::string ip = socket.remote_endpoint().address().to_string();
            uint16_t port = socket.remote_endpoint().port();
            d->DoRemoveClient(ip, port);
            tcpServer->deleteClientSignal(ip, port);
        }
    });

    const int maxLength = 10240;
    char data[maxLength] = {0};
    std::error_code error;
    while (1) {
        // block until data is read...
        size_t len = socket.read_some(asio::buffer(data, maxLength), error);
        if (error) {
            // asio::error::eof : Connection closed cleanly by peer.
            std::string ip = socket.remote_endpoint().address().to_string();
            uint16_t port = socket.remote_endpoint().port();
            d->DoRemoveClient(ip, port);
            tcpServer->deleteClientSignal(ip, port);
            break;
        }

        if (len <= 0) {
            continue;
        }

        tcpServer->bytesRxSignal(asio::const_buffer(data, len), d->serverAddress);
    }
}

void Listen(TCPServerPrivate *d, TCPServer *tcpServer)
{
    auto acceptor = d->acceptor;

    while (1) {
        try {
            tcp::socket socket = acceptor->accept();

            auto remoteEndpoint = socket.remote_endpoint();
            std::string ip = remoteEndpoint.address().to_string();
            uint16_t port = remoteEndpoint.port();

            d->clients.push_back(std::make_pair(ip, port));
            tcpServer->newClientSignal(ip, port);

            std::thread t(SetUpSocket, d, tcpServer, std::move(socket));
            t.detach();
        } catch (asio::system_error &e) {
            wxToolsInfo() << e.what() << e.code();
            break;
        }
    }

    delete acceptor;
    wxToolsInfo() << "server closed";
}

bool TCPServer::Open()
{
    Close();

    try {
        std::string ip = d->serverAddress.ToStdString();
        tcp::endpoint endpoint(asio::ip::make_address(ip), d->serverPort);
        d->acceptor = new tcp::acceptor(d->context, endpoint);
    } catch (std::exception &e) {
        wxToolsInfo() << "Open tcp server failed: " << e.what();
        return false;
    }

    std::thread t(Listen, d, this);
    t.detach();

    return true;
}

void TCPServer::Close()
{
    if (d->acceptor) {
        d->acceptor->close();
        d->acceptor = nullptr;
    }
}

void TCPServer::Write(const wxString &data, TextFormat format)
{
    d->invokeWriteSignal(data.ToStdString(), static_cast<int>(format));
}
