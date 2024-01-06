//
// Created by beloin on 05/01/24.
//

#ifndef TWAMP_MESSAGES_H
#define TWAMP_MESSAGES_H

namespace Network {

    struct ServerGreetings {
        char _unused[12];
        char modes[4];
        char challenge[16];
        char salt[16];
        char count[4];
        char mbz[12];
    };

    struct ClientGreetings {
        char mode[4];
        char key_id[80];
        char token[64];
        char client_iv[16];
    };

}

#endif //TWAMP_MESSAGES_H
