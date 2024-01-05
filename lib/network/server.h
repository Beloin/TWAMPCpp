//
// Created by beloin on 04/01/24.
//

#ifndef TWAMP_SERVER_H
#define TWAMP_SERVER_H

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
    };


}


#endif //TWAMP_SERVER_H
