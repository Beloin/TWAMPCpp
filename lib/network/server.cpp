//
// Created by beloin on 04/01/24.
//
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "spdlog/spdlog.h"

#include "server.h"
#include "utils/socket_utils.h"
#include "messages.h"

#define BACKLOG 10

using Network::Server;

void handle_socket(int client_fd);

int Server::Serve(const std::string &port) {
    int server_fd;
    struct addrinfo hints{}, *servinfo, *p;

    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(nullptr, port.data(), &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    }


    for (p = servinfo; p != nullptr; p = p->ai_next) {
        // This get socket information
        if ((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("serve: socket");
            continue;
        }

        // This enables re-utilization of ports
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        if (bind(server_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(server_fd);
            perror("serve: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);
    if (p == nullptr) {
        spdlog::error("serve: failed to bind");
        exit(1);
    }

    if (listen(server_fd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    spdlog::info("serve ({}): waiting for connections...", port);

    server_on = true;
    serverfd = server_fd;

    while (should_run) {
        struct sockaddr_storage their_addr{};
        socklen_t sin_size = sizeof their_addr;

        // Accept is a cancellation point, so we should be able to kill the serve thread here
        int new_fd = accept(server_fd, (struct sockaddr *) &their_addr, &sin_size);

        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family, Utils::get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
        spdlog::info("serve: got connection from {} with fd {}", s, new_fd);

        handle_socket(new_fd);
    }


    return 0;
}

Server::Server() : should_run(true), server_on(false) {}

Network::Server::~Server() {
    server_on = false;
    should_run = false;
    close(serverfd);

    // TODO: Kill clients
}

bool Network::Server::IsRunning() const {
    return server_on;
}


using namespace Network;

// TODO: Remember to use threads to retrieve more sockets;
void handle_socket(int client_fd) {
    size_t size;
    auto *buf = (unsigned char *) "Hello World";
    Network::ServerGreetings server_greetings{};

    size = sizeof(server_greetings);
    std::memset(&server_greetings, 0, size);
    server_greetings.modes[3] = 1;

    auto *buff = new unsigned char[64]; // unsigned char buffer[64];
    int bytes_written = Network::SerializeServerGreetings(server_greetings, buff);

    spdlog::debug("sending {} bytes to client with fd {}", bytes_written, client_fd);
    size_t bytes_sent = Utils::sbytes(client_fd, buff, bytes_written);
//    size_t bytes_sent = Utils::sbytes(client_fd, buf, 12);
    if (bytes_sent != bytes_written) {
        if (bytes_sent == -1) {
            spdlog::info("could not send this message to client (fd:{})", client_fd);
        } else {
            spdlog::info("client (fd:{}) disconnected", client_fd);
        }
        // Normally errors like this are some kind of connection end like: EINTR
    }

    close(client_fd);

    delete[] buff;
}
