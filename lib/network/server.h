//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_SERVER_H
#define TWAMP_SERVER_H

#include "connected_client.h"

#define SERVWAIT 900
#define REFWAIT 900

// TODO: Use configuration. If we use dynamic configured, we will need a vector or a list
#define MAX_CLIENTS 2

namespace Network {

    class Server {

    public:
        explicit Server();

        int Serve(const std::string &port);

        ~Server();

        bool IsRunning() const;

    private:
        bool should_run;
        bool server_on;
        int serverfd{};

        long start_time_ms{};
        uint32_t st_integer_part{};
        uint32_t st_fractional_part{};

        int client_amount = 0;
        std::vector<ConnectedClient> clients{};

        void handle_socket(int client_fd, std::string client_addr);
    };


}


#endif //TWAMP_SERVER_H
