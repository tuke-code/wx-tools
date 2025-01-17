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

void Loop(TCPClientPrivate *d, TCPClient *tcpClient)
{
    asio::io_context context;
    tcp::socket s(context);
    tcp::resolver resolver(context);
    std::string ip = d->serverAddress.ToStdString();
    std::string port = std::to_string(d->serverPort);
    try {
        asio::connect(s, resolver.resolve(ip, port));
    } catch (const asio::system_error &e) {
        wxToolsWarning() << "Connect to server failed: " << e.what();
        return;
    }

    char data[1024] = {0};
    std::atomic_bool stop(false);

    while (1) {
        if (stop.load()) {
            break;
        }

        s.async_read_some(asio::buffer(data, 1024), [&](std::error_code e, std::size_t len) {
            if (e) {
                stop.store(true);
                return;
            } else {
                if (len <= 0) {
                    return;
                }

                wxToolsInfo() << "Read data from server: " << data;
                std::string flag = SocketBase::DoEncodeFlag(ip, d->serverPort);
                tcpClient->bytesRxSignal(asio::const_buffer(data, len), flag);
            }
        });

        d->msgMutex.lock();
        for (auto &msg : d->msgList) {
            try {
                size_t len = asio::write(s, asio::buffer(msg.first));
                std::string flag = SocketBase::DoEncodeFlag(ip, d->serverPort);
                tcpClient->bytesTxSignal(asio::const_buffer(msg.first.c_str(), len), flag);
            } catch (std::system_error e) {
                wxToolsWarning() << "Write data to server failed: " << e.what();
                stop.store(true);
            }
        }
        d->msgList.clear();
        d->msgMutex.unlock();

        // sleep 50ms
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    wxToolsInfo() << "TCP client loop exit";
}

bool TCPClient::Open()
{
    std::thread t(Loop, d, this);
    t.detach();

    return true;
}

void TCPClient::Close()
{
    
}

void TCPClient::Write(const wxString &data, TextFormat format)
{
    d->msgMutex.lock();
    d->msgList.push_back(std::make_pair(data.ToStdString(), static_cast<int>(format)));
    d->msgMutex.unlock();
}
