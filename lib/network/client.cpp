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

double parse_server_start(Network::ServerStart &server_start);

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
    server_addr = s;
    freeaddrinfo(servinfo);

    has_connected = true;

    return 0;
}

void Network::Client::StartConnection() {
    unsigned char buffer[200];
    ssize_t read;

    if (!has_connected) {
        spdlog::info("server not connected");
        return;
    }
    ServerGreetings serverGreetings{};

    // Should check here too
    read = readServerGreetings(buffer, serverGreetings);
    if (read <= 0 || serverGreetings.modes[3] != 1) { // Not accept anything besides unauthenticated mode
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

    ServerStart server_start{};
    read = readServerStart(buffer, server_start);

    if (read <= 0 || server_start.mbz[15] != 0) {
        spdlog::error("could not get `Server-Start` message: Bytes read {}", read);
        close(server_fd);
        return;
    }

    double ms = parse_server_start(server_start);
    spdlog::info("connection successfully with server {}. Time alive: {}", server_addr, ms);
}

double parse_server_start(Network::ServerStart &server_start) {
    uint32_t st_integer_part = 0;
    uint64_t st_fractional_part = 0; // TODO: Fix this
    for (int i = 0; i < 4; ++i) {
        int offset = 8 * (i + 1);

        uint32_t temp = server_start.start_time[i];
        temp <<= (32 - offset);
        st_integer_part |= temp;

        temp = server_start.start_time[4 + i];;
        temp <<= (32 - offset);
        st_fractional_part |= temp;
    }

//    st_fractional_part >>= 1; // removes
    union {
        uint64_t bits;
        double real;
    } value = {st_fractional_part}; // 000000000000_20=0_32=(st_fractional_part)
    value.bits <<= 19;
    value.bits |= 1ULL << 20;
    value.bits |= 0x3FFULL << 52;
    return ((double) st_integer_part) + value.real;
}


ssize_t Network::Client::readServerStart(unsigned char *buffer, Network::ServerStart &server_start) const {
    ssize_t read;
    read = Utils::rbytes(server_fd, buffer, 64);
    server_start.Deserialize(buffer);
    return read;
}

ssize_t Network::Client::readServerGreetings(unsigned char *buffer, Network::ServerGreetings &serverGreetings) const {
    ssize_t r = Utils::rbytes(server_fd, buffer, 64);
    serverGreetings.Deserialize(buffer);
    return r;
}

Network::Client::~Client() {
    close(server_fd);
}

void Network::Client::StartTestSession() {

}
