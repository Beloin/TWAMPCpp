//
// Created by beloin on 29/01/24.
//

#include "connected_client.h"

#include <csignal>

// Remember to use rvalue to prevent an unnecessary copy
Network::ConnectedClient::ConnectedClient(std::string& host, int id, int fd) : host(std::move(host)), id(id), fd(fd) {}

Network::ConnectedClient::~ConnectedClient() {
    close(fd);
}
