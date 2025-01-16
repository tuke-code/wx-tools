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
    delete d;
    d = nullptr;
}

void ReadData(UDPServerPrivate *d, UDPServer *udpServer)
{
    udp::resolver resolver(d->context);
    std::string host = d->serverAddress.ToStdString();
    std::string port = std::to_string(d->serverPort);

    while (1) {
        char buffer[10240] = {0};
        udp::endpoint sender;
        try {
            size_t len = d->socket->receive_from(asio::buffer(buffer, 10240), sender);
            if (len <= 0) {
                continue;
            }

            // If the client is not in the list, add it.
            auto pair = std::make_pair(sender.address().to_string(), sender.port());
            if (std::find(d->clients.begin(), d->clients.end(), pair) == d->clients.end()) {
                d->clients.push_back(pair);
                udpServer->newClientSignal(sender.address().to_string(), sender.port());
                wxToolsInfo() << "New client: " << sender.address().to_string() << ":"
                              << sender.port();
            }

            std::string data(buffer, len);
            asio::const_buffer buffer(data.data(), data.size());
            udpServer->bytesReadSignal(buffer, d->serverAddress);
        } catch (asio::system_error &e) {
            if (e.code().value() != 10004) {
                wxToolsInfo() << e.what();
            }

            break;
        }
    }
}

bool UDPServer::Open()
{
    Close();

    udp::endpoint endpoint(asio::ip::make_address(d->serverAddress.ToStdString()), d->serverPort);
    d->socket = new udp::socket(d->context, endpoint);
    if (!d->socket) {
        return false;
    }

    std::thread t(ReadData, d, this);
    t.detach();

    return true;
}

void UDPServer::Close()
{
    if (d->socket) {
        d->socket->close();
        delete d->socket;
        d->socket = nullptr;
    }
}

void WriteData(UDPServerPrivate *d,
               UDPServer *udpServer,
               const std::string &address,
               uint16_t port,
               const wxToolsConstBuffer &buffer)
{
    udp::endpoint endpoint(asio::ip::make_address(address), port);
    size_t len = d->socket->send_to(buffer, endpoint);
    if (len > 0) {
        udpServer->bytesWrittenSignal(buffer, wxString(udpServer->DoEncodeFlag(address, port)));
    } else {
        // If send failed, I think the client is disconnected, so remove it.
        d->DoRemoveClient(address, port);
        udpServer->deleteClientSignal(address, port);
    }
}

void UDPServer::Write(const wxString &data, TextFormat format)
{
    wxToolsConstBuffer buffer = DoEncodeText(data.ToStdString(), format);
    if (d->selection.first.empty() && d->selection.second == 0) {
        // Send to all clients.
        for (const std::pair<std::string, uint16_t> &pair : d->clients) {
            WriteData(d, this, pair.first, pair.second, buffer);
        }
    } else {
        // Send to the selected client.
        WriteData(d, this, d->selection.first, d->selection.second, buffer);
    }
}
