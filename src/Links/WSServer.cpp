/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSServer.h"
#include "WSServer_p.h"

WSServer::WSServer()
    : SocketServer(d = new WSServerPrivate)
{}

WSServer::~WSServer()
{
    Close();

    delete d;
    d = nullptr;
}

bool WSServer::Open()
{
    std::string ip = d->serverAddress.ToStdString();
    uint16_t port = d->serverPort;

    std::thread t(WSServerLoop, d, this);
    t.detach();

    while (!d->running) {
        // Wait for server to start
        break;
    }

    d->bytesRx.connect([](std::shared_ptr<char> bytes, int len, std::string from) {
        wxToolsInfo() << "Received " << len << " bytes from " << from;
    });
    d->bytesTx.connect([](std::shared_ptr<char> bytes, int len, std::string to) {
        wxToolsInfo() << "Transmitted " << len << " bytes to " << to;
    });
    d->errorOccurred.connect([](std::string error) {
        wxToolsWarning() << "Error occurred: " << error << ". The server will be interrupted!";
    });

    return true;
}

void WSServer::Close()
{
    if (d) {
        d->invokedInterrupted.store(true);
        while (!d->running) {
            // Wait for server to stop
            break;
        }

        d->errorOccurred.disconnect_all();
        d->bytesRx.disconnect_all();
        d->bytesTx.disconnect_all();
    }
}

void WSServer::Write(const wxString &data, TextFormat format)
{
    int len = 0;
    std::shared_ptr<char> bytes = DoEncodeBytes(data.ToStdString(), len, static_cast<int>(format));
    if (len > 0) {
        d->txBytes.push_back(std::make_pair(std::move(bytes), len));
    }
}
