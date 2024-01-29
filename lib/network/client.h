//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_CLIENT_H
#define TWAMP_CLIENT_H

#include <string>
#include "messages.h"

namespace Network {
    class Client {

    private:
        bool has_connected = false;
        int server_fd{};

        std::string server_addr;
        double server_start_ms;

        int UpdaterServerFd(std::string const &host, std::string const &port);

    public:
        int ConnectTo(std::string const &host, std::string const &port);

        void StartConnection();

        ssize_t readServerGreetings(unsigned char *buffer, Network::ServerGreetings &serverGreetings) const;

        ssize_t readServerStart(unsigned char *buffer, ServerStart &server_start) const;
    };

}


#endif //TWAMP_CLIENT_H
