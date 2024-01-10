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
            perror("client: connect");
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

void Network::Client::Ping() {
    unsigned char buffer[100];

    if (!has_connected); // TODO: Create a validation here
    Utils::rbytes(server_fd, buffer, 64);
    ServerGreetings serverGreetings{};

    // TODO: Using it for test
    std::memset(&serverGreetings, 1, sizeof(serverGreetings));

    Network::DeserializeServerGreetings(serverGreetings, buffer);

    close(server_fd);
}
