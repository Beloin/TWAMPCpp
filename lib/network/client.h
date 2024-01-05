//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_CLIENT_H
#define TWAMP_CLIENT_H

#include <string>

namespace Network {
    class Client {

    private:
        int server_fd{};

        int UpdaterServerFd(std::string const &host, std::string const &port);

    public:
        int ConnectTo(std::string const &host, std::string const &port);

    };

}


#endif //TWAMP_CLIENT_H
