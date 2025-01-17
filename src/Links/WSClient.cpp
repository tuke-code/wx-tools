/***************************************************************************************************
 * Copyright 2024-2025 x-tools-author(x-tools@outlook.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part of eTools project.
 *
 * eTools is licensed according to the terms in the file LICENCE(GPL V3) in the root of the source
 * code directory.
 **************************************************************************************************/
#include "WSClient.h"
#include "WSClient_p.h"

WSClient::WSClient()
    : SocketClient(d = new WSClientPrivate)
{}

WSClient::~WSClient()
{
    Close();

    delete d;
    d = nullptr;
}

bool WSClient::Open()
{
    std::string ip = d->serverAddress.ToStdString();
    uint16_t port = d->serverPort;

    d->client = new WebSocketClient();
    std::thread t(WSClientLoop, d->client, ip, port);
    t.detach();

    while (!d->client->running) {
        // Wait for server to start
        break;
    }
#if 0
    d->client->bytesRx.connect([](std::shared_ptr<char> bytes, int len, std::string from) {
        wxToolsInfo() << "Received " << len << " bytes from " << from;
    });
    d->client->bytesTx.connect([](std::shared_ptr<char> bytes, int len, std::string to) {
        wxToolsInfo() << "Transmitted " << len << " bytes to " << to;
    });
    d->client->errorOccurred.connect([](std::string error) {
        wxToolsWarning() << "Error occurred: " << error << ". The server will be interrupted!";
    });
#endif

    return true;
}

void WSClient::Close()
{
    if (d->client) {
        d->client->invokedInterrupted.store(true);
        while (!d->client->running) {
            // Wait for server to stop
            break;
        }

        d->client->errorOccurred.disconnect_all();
        d->client->bytesRx.disconnect_all();
        d->client->bytesTx.disconnect_all();
        delete d->client;
        d->client = nullptr;
    }
}

void WSClient::Write(const wxString &data, TextFormat format)
{
    int len = 0;
    std::shared_ptr<char> bytes = DoCookeText(data.ToStdString(), static_cast<int>(format), len);
    if (len > 0) {
        d->client->txBytes.push_back(std::make_pair(std::move(bytes), len));
    }
}
