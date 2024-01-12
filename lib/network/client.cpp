//
// Created by beloin on 04/01/24.
//

#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

#include "spdlog/spdlog.h"

#include "utils/socket_utils.h"
#include "client.h"
#include "messages.h"

using Network::Client;


int Client::ConnectTo(const std::string &host, const std::string &port) {
    auto status = UpdaterServerFd(host, port);
    // TODO: Maybe here we can throw?
    return status;
}


int Client::UpdaterServerFd(std::string const &host, std::string const &port) {
    struct addrinfo hints{}, *servinfo, *p;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(host.data(), port.data(), &hints, &servinfo)) != 0) {
        spdlog::error("getaddrinfo: {}", gai_strerror(rv));
//        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    for (p = servinfo; p != nullptr; p = p->ai_next) {
        if ((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(server_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(server_fd);
            perror("client connect");
            continue;
        }

        break;
    }


    if (p == nullptr) {
        spdlog::error("client: failed to connect");
        return 3;
    }

    inet_ntop(p->ai_family, Utils::get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof s);
    spdlog::info("client: connecting to {} with fd {}", s, server_fd);
    freeaddrinfo(servinfo);

    has_connected = true;

    return 0;
}

void Network::Client::StartConnection() {
    unsigned char buffer[200];

    if (!has_connected) {
        spdlog::info("server not connected");
        return;
    }

    // Should check here too
    Utils::rbytes(server_fd, buffer, 64);

    ServerGreetings serverGreetings{};
    serverGreetings.Deserialize(buffer);

    if (serverGreetings.modes[3] != 1) { // Not accept anything besides unauthenticated mode
        close(server_fd);
        return;
    }

    ClientGreetings clientGreetings{};
    std::memset(&clientGreetings, 0, sizeof(ClientGreetings)); // Not necesary since we are using char x[N] = {0};

    clientGreetings.mode[3] = 1;
    int size = clientGreetings.Serialize(buffer); // 164 bytes

    size_t bytes_sent = Utils::sbytes(server_fd, buffer, size); // TODO: Generate error when return != size
    if (bytes_sent != size) {
        if (bytes_sent == -1) {
            spdlog::info("could not send this message to server (fd:{})", server_fd);
        } else {
            spdlog::info("server (fd:{}) disconnected", server_fd);
        }
        // Normally errors like this are some kind of connection end like: EINTR
    }

    close(server_fd);
}
