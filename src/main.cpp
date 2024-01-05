//
// Created by beloin on 28/12/23.
//
#include <iostream>

#include "utils/setup_logger.h"
#include "spdlog/spdlog.h"
#include "network/server.h"
#include "network/client.h"

#define PORT "8862" // Should be 862

void client_main();

[[noreturn]] int main(int arv, char **argc) {
    Network::Server server;
    Setup::setup_logger(Setup::logger_info_tag{}); // Tags used merely as example

    while (true) {
        server.Serve(PORT);
    }
//    client_main();
}

void client_main() {
    Network::Client client{};

    client.ConnectTo("127.0.0.1", PORT);
    client.Ping();
}