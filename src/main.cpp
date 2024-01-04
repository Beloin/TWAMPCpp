//
// Created by beloin on 28/12/23.
//
#include <iostream>

#include "utils/setup_logger.h"
#include "spdlog/spdlog.h"
#include "network/server.h"


[[noreturn]] int main(int arv, char **argc) {
    Network::Server server{};

    Setup::setup_logger(Setup::logger_info_tag{}); // Tags used merely as example

    std::cout << "Hello World" << std::endl;
    while (true) {
        server.Serve("8862"); // Should be 862
    }
}