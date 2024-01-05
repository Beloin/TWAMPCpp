#! /usr/bin/python
# a simple tcp client
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('127.0.0.1', 8862))
# sock.send('Test\n')
# sock.send(raw_input("Please input : "))

s = sock.recv(11)

print(s)
sock.close()
