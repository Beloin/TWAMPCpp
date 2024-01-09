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

void Network::DeserializeServerGreetings(const Network::ServerGreetings &greetings, unsigned char *buf) {

}


