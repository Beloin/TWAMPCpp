//
// Created by beloin on 06/02/24.
//

#include "test_session.h"
#include <cstddef>
#include <cstring>
#include <endian.h>
#include <sys/types.h>

int Network::RequestTWSession::Serialize(unsigned char *buf) const {
  return 0;
}

int Network::RequestTWSession::Deserialize(const unsigned char *buf) {
  command = buf[0];
  ipvn = buf[1]; // MBZ can be obfuscated
  conf_sender = buf[2];
  conf_receiver = buf[3];

  uint32_t slots;
  memcpy(&slots, buf+4, sizeof(slots));
  scheduled_slots = be32toh(slots);

  // To calculate time:
  // be64toh(x)
  return 0;
}
