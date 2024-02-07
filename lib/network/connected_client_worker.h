//
// Created by beloin on 29/01/24.
//

#ifndef TWAMP_CONNECTED_CLIENT_WORKER_H
#define TWAMP_CONNECTED_CLIENT_WORKER_H

#include "string"

namespace Network {

    class ConnectedClientWorker {

    private:
        std::string host;

        int id = -1;
        int fd = -1;

    public:
        ConnectedClientWorker(std::string &host, int id, int fd);

        virtual ~ConnectedClientWorker();

        void operator()(); // Implement waits here
    };

}
#endif //TWAMP_CONNECTED_CLIENT_WORKER_H
