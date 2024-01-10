//
// Created by beloin on 05/01/24.
//

#include <netinet/in.h>
#include "messages.h"
#include "cstring"

/**
 *
 * @param greetings
 * @param buf at least 64 bytes
 * @return bytes written
 */
int Network::SerializeServerGreetings(const ServerGreetings &greetings, unsigned char *buf) {
    // TODO: See a better way to create this
    int current_pt = 0;
    for (auto c: greetings._unused) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: greetings.modes) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: greetings.challenge) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: greetings.salt) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: greetings.count) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: greetings.mbz) {
        buf[current_pt] = c;
        current_pt++;
    }

    // htons(); // Not necessary since we are using only chars

    return current_pt;
}

int Network::DeserializeServerGreetings(Network::ServerGreetings &greetings, const unsigned char *buf) {
    // ntohs(); // Not necessary since we are using only chars

    int last_index = 0;
    for (int i = 0; i < 12; ++i) {
        greetings._unused[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 4; ++i) {
        greetings.modes[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 16; ++i) {
        greetings.challenge[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 16; ++i) {
        greetings.salt[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 4; ++i) {
        greetings.count[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 12; ++i) {
        greetings.mbz[i] = buf[last_index];
        last_index++;
    }

    return last_index;
}


