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

<div style="text-align: center;">
    <img src="./resources/Twamp_overall_CLIENT_SERVER.png" alt="Control-Connection Sequence Diagram">
</div>

# Modus Operadis

Following [Chapter 5][5] from [__RFC 5357__][1] will be the Controller(Client) and
the Responder(Server), which will implement Session-Sender and Session Reflector respectively.

- [ ] TWAMP-Control:
    - [ ] Connection Setup
    - [ ] Integrity Protection
    - [ ] Connection Setup
    - [ ] TWAMP-Control Commands
    - [ ] Create Test Sessions
    - [ ] Send Schedules
    - [ ] Start Test Sessions
    - [ ] Stop Test Sessions
    - [ ] Fetch Session
- [ ] TWAMP-Test
    - Sender Behaviour
        - [ ] Packet Timings
        - [ ] Packet Format and Content
    - Reflector Behaviour
        - [ ] TWAMP-Test Packet Format and Content

# References

[1]:https://datatracker.ietf.org/doc/html/rfc5357

[2]:https://www.juniper.net/documentation/us/en/software/junos/flow-monitoring/topics/concept/twamp-overview.html

[3]:https://beej.us/guide/bgnet/

[5]:https://datatracker.ietf.org/doc/html/rfc5357#section-5

1. [RFC 5357][1]
2. [Understand Two-Way Active Measurement Protocol][2]
3. [Beej's Guide to Network Programming][3]

# Other Beloin's Projects

1. [Swarm Engine](https://github.com/Beloin/SwarmEngine)
1. [Distributed Game](https://github.com/Beloin/DistributedGame)
1. [Swarm Engine](https://github.com/Beloin/LCD_Rasp_Weather)

