/***************************************************************************************************
 * Copyright 2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#pragma once

#include <asio.hpp>

#include "SocketClient_p.h"

class AsioUdpClient
{
public:
    AsioUdpClient(asio::io_context &ioContext, short port)
        : m_socket(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
        doReceive();
    }

    void doReceive()
    {
        m_socket.async_receive_from(asio::buffer(m_data, MaxLength),
                                    m_senderEndpoint,
                                    [this](std::error_code ec, std::size_t bytes_recvd) {
                                        if (!ec && bytes_recvd > 0) {
                                            doSend(bytes_recvd);
                                        } else {
                                            doReceive();
                                        }
                                    });
    }

    void doSend(std::size_t length)
    {
        m_socket.async_send_to(asio::buffer(m_data, length),
                               m_senderEndpoint,
                               [this](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
                                   doReceive();
                               });
    }

private:
    asio::ip::udp::socket m_socket;
    asio::ip::udp::endpoint m_senderEndpoint;
    enum { MaxLength = 1024 };
    char m_data[MaxLength];
};

class UDPClientPrivate : public SocketClientPrivate
{
public:
    asio::io_context ioContext;
    asio::ip::udp::socket *socket{nullptr};
    asio::ip::udp::endpoint endpoint;
};
