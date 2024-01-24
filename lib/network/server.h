//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_SERVER_H
#define TWAMP_SERVER_H

#define SERVWAIT 900
#define REFWAIT 900

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

        // TODO: Create a client list

        void handle_socket(int client_fd);
    };


}


#endif //TWAMP_SERVER_H
