//
// Created by beloin on 06/02/24.
//

#ifndef TWAMP_TEST_SESSION_H
#define TWAMP_TEST_SESSION_H

#include <cstdint>

namespace Network {


    constexpr int REQUEST_TW_SESSION_SIZE = 112;

/**
 * Client message to Request a TWAMP Test Session
 */
    struct RequestTWSession {
        char command = {0};
        char ipvn = 4; // Must be set to 4

        char conf_sender{0};
        char conf_receiver{0};

        uint16_t sender_port{0};
        uint16_t receiver_port{0};

        char sender_address[4] = {0};
        char receiver_address[4] = {0};

        double start_time{0};
        uint64_t timeout{0};

        int Serialize(unsigned char *buf) const;

        int Deserialize(const unsigned char *buf);
    };

    struct AcceptSession {
        int Serialize(unsigned char *buf) const;

        int Deserialize(const unsigned char *buf);
    };

}
#endif //TWAMP_TEST_SESSION_H
