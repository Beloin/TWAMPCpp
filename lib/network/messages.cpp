//
// Created by beloin on 05/01/24.
//

#include <netinet/in.h>
#include "messages.h"

// TODO: Use function please
#define Serialize_char_arr(out, current_pt, in) for(auto c : out) { in[current_pt] = c; current_pt++; }
#define Deserialize_char_arr(out, current_pt, in) for(auto &c : out) { c = in[current_pt]; current_pt++; }

/**
 *
 * @param greetings
 * @param buf at least 64 bytes
 * @return bytes written
 */
int Network::ServerGreetings::Serialize(unsigned char *buf) const {
    // htons(); // Not necessary since we are using only chars

    // TODO: See a better way to create this
    int current_pt = 0;
    for (auto c: _unused) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: modes) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: challenge) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: salt) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: count) {
        buf[current_pt] = c;
        current_pt++;
    }

    for (auto c: mbz) {
        buf[current_pt] = c;
        current_pt++;
    }


    return current_pt;
}

int Network::ServerGreetings::Deserialize(const unsigned char *buf) {
    // ntohs(); // Not necessary since we are using only chars

    int last_index = 0;
    for (int i = 0; i < 12; ++i) {
        this->_unused[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 4; ++i) {
        this->modes[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 16; ++i) {
        this->challenge[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 16; ++i) {
        this->salt[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 4; ++i) {
        this->count[i] = buf[last_index];
        last_index++;
    }

    for (int i = 0; i < 12; ++i) {
        this->mbz[i] = buf[last_index];
        last_index++;
    }

    return last_index;
}


int Network::ClientGreetings::Serialize(unsigned char *buf) const {
    int current_pt = 0;

    Serialize_char_arr(mode, current_pt, buf);
    Serialize_char_arr(key_id, current_pt, buf);
    Serialize_char_arr(token, current_pt, buf);
    Serialize_char_arr(client_iv, current_pt, buf);

    return current_pt;
}

int Network::ClientGreetings::Deserialize(const unsigned char *buf) {
    int current_pt = 0;

    Deserialize_char_arr(mode, current_pt, buf);
    Deserialize_char_arr(key_id, current_pt, buf);
    Deserialize_char_arr(token, current_pt, buf);
    Deserialize_char_arr(client_iv, current_pt, buf);

    return current_pt;
}

int Network::ServerStart::Serialize(unsigned char *buf) const {
    int current_pt = 0;

    Serialize_char_arr(mbz, current_pt, buf);
    Serialize_char_arr(server_iv, current_pt, buf);
    Serialize_char_arr(start_time, current_pt, buf);
    Serialize_char_arr(_mbz, current_pt, buf);

    return current_pt;
}

int Network::ServerStart::Deserialize(const unsigned char *buf) {
    int current_pt = 0;

    Deserialize_char_arr(mbz, current_pt, buf);
    Deserialize_char_arr(server_iv, current_pt, buf);
    Deserialize_char_arr(start_time, current_pt, buf);
    Deserialize_char_arr(_mbz, current_pt, buf);

    return current_pt;
}
