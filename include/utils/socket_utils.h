//
// Created by beloin on 03/01/24.
//

#ifndef TWAMP_SOCKET_UTILS_H
#define TWAMP_SOCKET_UTILS_H

#include <cstddef>
#include <netinet/in.h>
#include <sys/socket.h>


namespace Utils {
    size_t rbytes(int socketfd, unsigned char *buf, size_t n);

    size_t sbytes(int socketfd, unsigned char *buf, size_t n);

    void *get_in_addr(struct sockaddr *sa);
}

#endif //TWAMP_SOCKET_UTILS_H
