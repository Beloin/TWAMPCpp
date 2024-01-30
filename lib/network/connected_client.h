//
// Created by beloin on 29/01/24.
//

#ifndef TWAMP_CONNECTED_CLIENT_H
#define TWAMP_CONNECTED_CLIENT_H

#include "string"

namespace Network {

    class ConnectedClient {

    private:
        std::string host;

        int id = -1;
        int fd = -1;

    public:
        ConnectedClient(std::string& host, int id, int fd);

        virtual ~ConnectedClient();
    };

}
#endif //TWAMP_CONNECTED_CLIENT_H
