//
// Created by beloin on 05/01/24.
//

#ifndef TWAMP_MESSAGES_H
#define TWAMP_MESSAGES_H

#include <ostream>

namespace Network {

    struct ServerGreetings {
        unsigned char _unused[12] = {0};
        unsigned char modes[4] = {0};
        unsigned char challenge[16] = {0};
        unsigned char salt[16] = {0};
        unsigned char count[4] = {0};
        unsigned char mbz[12] = {0};

        int Serialize(unsigned char *buf) const;

        int Deserialize(const unsigned char *buf);
    };

    struct ClientGreetings {
        unsigned char mode[4] = {0};
        unsigned char key_id[80] = {0};
        unsigned char token[64] = {0};
        unsigned char client_iv[16] = {0};

        int Serialize(unsigned char *buf) const;

        int Deserialize(const unsigned char *buf);
    };

    struct ServerStartMessage {
        unsigned char mbz[15] = {0}; // Accept is the last 1 byte
        unsigned char server_iv[16] = {0};
        unsigned char start_time[6] = {0};
        unsigned char _mbz[8] = {0};

        int Serialize(unsigned char *buf) const;

        int Deserialize(const unsigned char *buf);
    };

}

#endif //TWAMP_MESSAGES_H
