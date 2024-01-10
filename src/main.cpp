//
// Created by beloin on 28/12/23.
//
#include <iostream>

#include "utils/setup_logger.h"
#include "spdlog/spdlog.h"
#include "network/server.h"
#include "network/client.h"

#include <string>

#define PORT "8862" // Should be 862

void client_main();

// TODO: We will ignore DSCP?


[[noreturn]] int main(int argv, char **argc) {
    Network::Server server; // The Server and Session-Reflector
    Setup::setup_logger(Setup::logger_info_tag{}); // Tags used merely as example

    if (std::strcmp(argc[1], "server") == 0) {
        while (true) {
            server.Serve(PORT); // TODO: Implement server greetings
        }
    } else {
        client_main();
        exit(0);
    }

}

void client_main() {
    Network::Client client{}; // The Control-Client and Session-Sender

    client.ConnectTo("127.0.0.1", PORT);
    client.Ping();
}