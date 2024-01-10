//
// Created by beloin on 05/01/24.
//

#ifndef TWAMP_MESSAGES_H
#define TWAMP_MESSAGES_H

#include <ostream>

namespace Network {

    struct ServerGreetings {
        unsigned char _unused[12];
        unsigned char modes[4];
        unsigned char challenge[16];
        unsigned char salt[16];
        unsigned char count[4];
        unsigned char mbz[12];

//        friend std::ostream &operator<<(std::ostream &out, const ServerGreetings &c);
    };

    struct ClientGreetings {
        unsigned char mode[4];
        unsigned char key_id[80];
        unsigned char token[64];
        unsigned char client_iv[16];

//        friend std::ostream &operator<<(std::ostream &out, const ServerGreetings &c);
    };

    int SerializeServerGreetings(const ServerGreetings &greetings, unsigned char *buf);

    int DeserializeServerGreetings(ServerGreetings &greetings, const unsigned char *buf);
}

#endif //TWAMP_MESSAGES_H
