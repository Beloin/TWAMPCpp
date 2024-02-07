//
// Created by beloin on 06/02/24.
//

#ifndef TWAMP_TEST_SESSION_H
#define TWAMP_TEST_SESSION_H

struct RequestTWSession {
    char command;
    char mbz_ipvn;
    char conf_sender;
    char conf_reciever;
};

#endif //TWAMP_TEST_SESSION_H
