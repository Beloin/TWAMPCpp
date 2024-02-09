//
// Created by beloin on 29/01/24.
//

#include "connected_client_worker.h"
#include "utils/socket_utils.h"
#include "network/test_sessions/test_session.h"
#include "utils/time_utils.h"
#include <csignal>
#include <spdlog/spdlog.h>

using namespace Network;

typedef std::chrono::duration<double, std::ratio<1, 1>> duration_seconds;

bool is_zero(const char *s, char n);

// Remember to use rvalue to prevent an unnecessary copy
ConnectedClientWorker::ConnectedClientWorker(std::string &host, int id, int fd) : host(std::move(host)),
                                                                                  id(id), fd(fd) {}

ConnectedClientWorker::~ConnectedClientWorker() {
    if (!closed) close(fd);
}

void ConnectedClientWorker::operator()() {
    unsigned char buffer[REQUEST_TW_SESSION_SIZE];
    ssize_t read = Utils::rbytes(fd, buffer, REQUEST_TW_SESSION_SIZE);

    if (read != REQUEST_TW_SESSION_SIZE) {
        spdlog::info("client ({}) disconnected with fd {}", id, fd);
        CloseConnection();
        return;
    }

    RequestTWSession requestTwSession;
    requestTwSession.Deserialize(buffer);

    if (requestTwSession.command != 5) {
        // Return accept = 3
        spdlog::info("client ({}): command not acceptable", id);
        CloseConnection();
        return;
    }

    if (requestTwSession.ipvn != 4) {
        // Return accept = 3
        spdlog::info("client ({}): IPV4 only", id);
        CloseConnection();
        return;
    }

    if (!requestTwSession.conf_receiver || !requestTwSession.conf_sender) {
        // Return accept = 3
        spdlog::info("client ({}): request not supported", id);
        CloseConnection();
        return;
    }

    if (!is_zero(requestTwSession.sender_address, 4) || !is_zero(requestTwSession.receiver_address, 4)) {
        // Return accept = 3
        spdlog::info("client ({}): request not supported", id);
        CloseConnection();
        return;
    }


    sender_port = requestTwSession.sender_port;
    receiver_port = requestTwSession.receiver_port;
    timeout_s = requestTwSession.timeout;

    duration_seconds seconds{requestTwSession.start_time};
    auto ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(seconds);
    start_time = twamp_start_date() + ms_duration;

    // Send AcceptSession message
}

void ConnectedClientWorker::CloseConnection() {
    close(fd);
    closed = true;
}


bool is_zero(const char *s, char n) {
    char out = 0;
    for (int i = 0; i < n; ++i) {
        out |= s[i];
    }

    return out;
}