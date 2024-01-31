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
   |  |     Utils     |
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

Following [Chapter 5][5] (two-host implementation) from [__RFC 5357__][1] will be the Controller(Client) and
the Responder(Server), which will implement Session-Sender and Session Reflector respectively.

- [ ] TWAMP-Control:
    - [ ] Connection Setup
    - [ ] Integrity Protection (Probably will not be implemented) (Implement later with shared-secrets)
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

## Connection Setup:

Same as [OWAMP][6], network byte order.

Packet:

``` 
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
|                      Unused (12 octets)                       |
|                                                               |
|+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            Modes                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
|                     Challenge (16 octets)                     |
|                                                               |
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
|                        Salt (16 octets)                       |
|                                                               |
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                        Count (4 octets)                       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                                                               |
|                        MBZ (12 octets)                        |
|                                                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

Timestamp:

The format of the timestamp is the same as in [RFC1305] and is as
follows: the first 32 bits represent the unsigned integer number of
seconds elapsed since 0h on 1 January 1900; the next 32 bits
represent the fractional part of a second that has elapsed since
then.

```
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                   Integer part of seconds                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                 Fractional part of seconds                    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

After connections is established, client can send the following commands: Request-Session, Start-Sessions,
Stop-Sessions and Fetch-Session.

## Creating Test Session

.. 

## About Floating Point Numbers

The developer had to implement own float [IEEE 754][10] parser to get integral and fractional part
of `timestamp`.

# Dependencies

1. [spdlog](https://github.com/gabime/spdlog)
    1. `pacman -S spdlog`
    2. `sudo apt install libspdlog-dev`

# References

[1]:https://datatracker.ietf.org/doc/html/rfc5357

[2]:https://www.juniper.net/documentation/us/en/software/junos/flow-monitoring/topics/concept/twamp-overview.html

[3]:https://beej.us/guide/bgnet/

[5]:https://datatracker.ietf.org/doc/html/rfc5357#section-5

[6]:https://datatracker.ietf.org/doc/html/rfc4656#section-3.1

[7]:https://stackoverflow.com/questions/283375/detecting-tcp-client-disconnect#:~:text=154,recvXXX()%20when%20reading.

[8]:https://en.wikipedia.org/wiki/Offset_binary

[9]:https://git.musl-libc.org/cgit/musl/tree/src/math/modf.c

[10]:https://en.wikipedia.org/wiki/Double-precision_floating-point_format

1. [RFC 5357][1]
2. [Understand Two-Way Active Measurement Protocol][2]
3. [Beej's Guide to Network Programming][3]
4. [Socket Disconnected][7]

# Other Beloin's Projects

1. [Swarm Engine](https://github.com/Beloin/SwarmEngine)
1. [Distributed Game](https://github.com/Beloin/DistributedGame)
1. [Swarm Engine](https://github.com/Beloin/LCD_Rasp_Weather)

