//
// Created by beloin on 29/01/24.
//

#ifndef TWAMP_CONNECTED_CLIENT_WORKER_H
#define TWAMP_CONNECTED_CLIENT_WORKER_H

#include <cstdint>
#include "chrono"
#include "string"

namespace Network {

    class ConnectedClientWorker {

    private:
        std::string host;
        bool closed{false};

        int id = -1;
        int fd = -1;

        std::chrono::system_clock::time_point start_time;

        uint64_t timeout_s{0};
        uint16_t sender_port{0};
        uint16_t receiver_port{0};


    public:
        ConnectedClientWorker(std::string &host, int id, int fd);

        virtual ~ConnectedClientWorker();

        void operator()(); // Implement waits here
        void CloseConnection();
    };

}
#endif //TWAMP_CONNECTED_CLIENT_WORKER_H
