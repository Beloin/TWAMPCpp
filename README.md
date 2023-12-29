# TWAMP C++ Implementation

TWAMP is a Two-Way Active Measurement Protocol designed to measuring metrics between two
network devices.

Simple Logic Diagram:

```
 +----------------+               +-------------------+
 | Session-Sender |<-TWAMP-Test-->| Session-Reflector |
 +----------------+               +-------------------+
   ^                                     ^
   |                                     |
   |                                     |
   |                                     |
   |  +----------------+<----------------+
   |  |     Server     |
   |  +----------------+
   |    ^
   |    |
   | TWAMP-Control
   |    |
   v    v
 +----------------+
 | Control-Client |
 +----------------+
```

Overview:

 


# References

1. [RFC 5357](https://datatracker.ietf.org/doc/html/rfc5357)
2. [Understand Two-Way Active Measurement Protocol](https://www.juniper.net/documentation/us/en/software/junos/flow-monitoring/topics/concept/twamp-overview.html)

# Other Beloin's Projects

1. [Swarm Engine](https://github.com/Beloin/SwarmEngine)
1. [Distributed Game](https://github.com/Beloin/DistributedGame)
1. [Swarm Engine](https://github.com/Beloin/LCD_Rasp_Weather)

