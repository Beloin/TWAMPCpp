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

using namespace Network;

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

uint32_t get_frac(double value);

Server::Server() : should_run(true), server_on(false) {
    using std::chrono::milliseconds;
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    auto ms_since_epoch = std::chrono::duration_cast<milliseconds>(epoch);

    // Not using double to
    auto ms = (double) ms_since_epoch.count(); // TODO: Change to since 0h on 1 January 1900
    auto value = ms / 1000; // Seconds to float works as expected till  va
    double debug_cp = value;

    st_integer_part = (int32_t) value;
    st_fractional_part = get_frac(1.75);
}

uint32_t get_frac(double value) {
//    double frac = modf(value, nullptr); // TODO: Ignore this
    auto *p = reinterpret_cast<uint64_t *>(&value);
    // Or:
    union {
        double db;
        uint64_t i;
    } pp = {value};

    // Inspired by: https://git.musl-libc.org/cgit/musl/tree/src/math/modf.c

    // 52 -> mantissa
    // 0x7FF -> Mask sign and 10 less significant bits exponent
    // 0x3FF -> bias => https://en.wikipedia.org/wiki/Offset_binary
    uint64_t full_exp = (pp.i >> 52) & 0x7FF;
    int real_exp = (int) (full_exp - 0x3FF);

    // There's no fraction part
    if (real_exp >= 52) return 0;

    // There's no integral part
    if (real_exp < 0) {
        auto i1 = (uint32_t) (value * pow(10, 10)); // 10 is the precision
        return i1;
    }

    // "-1ULL" => 11111111_11111111_...
    // "<<12" => Zero the exponent and sign
    // "real_exp" => The resultant integer part mask
    uint64_t mask = -1ULL >> 12 >> real_exp;
    if ((pp.i & mask) == 0) { // Again there's no fraction
        return 0;
    }

    // TODO: I think we can sent the fractional part as it is in double
    // Example for 1.75: Fractional == 0.11, so we sent this 11
    pp.i &= ~mask; // Retrieve only integer part
    double only_frac = value - pp.db;
    auto i1 = (uint32_t) (only_frac * pow(10, 5)); // 10 is the precision
    return i1;
}

Network::Server::~Server() {
    server_on = false;
    should_run = false;
    close(serverfd);

    // TODO: Kill clients
}

bool Network::Server::IsRunning() const {
    return server_on;
}

void parse_decimal_float(ServerStart &start_message, uint32_t integer);

void Network::Server::handle_socket(int client_fd) {
    // TODO: Remember to use threads to retrieve more sockets;
    ssize_t size;
    Network::ServerGreetings server_greetings{};

    size = sizeof(server_greetings);
    std::memset(&server_greetings, 0, size); // Not necessary anymore
    server_greetings.modes[3] = 1;

    auto *buff = new unsigned char[200]; // unsigned char buffer[64]; Used `new` to be used to using delete[]
    int bytes_written = server_greetings.Serialize(buff);

    spdlog::debug("sending {} bytes to client with fd {}", bytes_written, client_fd);
    ssize_t bytes_sent = Utils::sbytes(client_fd, buff, bytes_written);
    if (bytes_sent != bytes_written) {
        if (bytes_sent == -1) {
            spdlog::info("could not send this message to client (fd:{})", client_fd);
        } else {
            spdlog::info("client (fd:{}) disconnected", client_fd);
        }
        // Normally errors like this are some kind of connection end like: EINTR
    }

    bytes_sent = Utils::rbytes(client_fd, buff, 164);
    if (bytes_sent != 164) {
        if (bytes_sent == -1) {
            spdlog::info("could not send read this message from client (fd:{})", client_fd);
        } else {
            spdlog::info("client (fd:{}) disconnected", client_fd);
        }
    }

    ClientGreetings client_greetings{};
    client_greetings.Deserialize(buff);

    if (client_greetings.mode[3] != 1) {
        spdlog::info("client rejected connection with mode {}", client_greetings.mode[3]);
        close(client_fd);
        return;
    }

    ServerStart start_message{};

    parse_decimal_float(start_message, st_integer_part);
    start_message.Serialize(buff);
    if ((bytes_sent = Utils::sbytes(client_fd, buff, 64)) != 64) {
        spdlog::error("could not send `Server-Start` message: Bytes sent = {}", bytes_sent);
        close(client_fd);
    }

    close(client_fd);

    delete[] buff;
}

void parse_decimal_float(ServerStart &start_message, uint32_t integer) {
    for (int i = 0; i < 4; ++i) {
        start_message.start_time[4 - i] = // Shouldn't be 4?
                integer >> (32 - (8 * (i + 1))); // 11101110...00000000 >> (24) => 00000000...11101110
    }
}
