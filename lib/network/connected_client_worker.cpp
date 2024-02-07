//
// Created by beloin on 29/01/24.
//

#include "connected_client_worker.h"

#include <csignal>

// Remember to use rvalue to prevent an unnecessary copy
Network::ConnectedClientWorker::ConnectedClientWorker(std::string& host, int id, int fd) : host(std::move(host)), id(id), fd(fd) {}

Network::ConnectedClientWorker::~ConnectedClientWorker() {
    close(fd);
}
