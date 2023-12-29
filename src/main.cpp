//
// Created by beloin on 28/12/23.
//
#include <iostream>

#include "setup_logger.h"
#include "spdlog/spdlog.h"

[[noreturn]] int main(int arv, char **argc) {
    Setup::setup_logger(Setup::logger_info_tag{}); // Tags used merely as example

    std::cout << "Hello World" << std::endl;
}