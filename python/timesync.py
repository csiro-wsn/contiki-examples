#!/usr/bin/python

import socket
import time
import datetime
import struct
import StringIO
from threading import Thread
import sys


UDP_TIMESYNC_PORT = 4003 # node listens for timesync packets on port 4003
UDP_REPLY_PORT = 7005 # node listens for reply packets on port 7005

isRunning = True

def udpListenThread():

  # listen on UDP socket port UDP_TIMESYNC_PORT
  recvSocket = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
  recvSocket.bind(("fec0::100", UDP_REPLY_PORT))
  recvSocket.settimeout(0.5)

  while isRunning:
    
    try:
      data, addr = recvSocket.recvfrom( 1024 )
      timestamp = (struct.unpack("I", data[0:4]))[0]
      utc = datetime.datetime.fromtimestamp(timestamp)
      print "Reply from:", addr[0], "UTC[s]:", timestamp, "Localtime:", utc.strftime("%Y-%m-%d %H:%M:%S")
    except socket.timeout:
      pass
    
def udpSendThread():

  sock = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM, 0)

  while isRunning:
    timestamp = int(time.time())
    print "Sending timesync packet with UTC[s]:", timestamp, "Localtime:", time.strftime("%Y-%m-%d %H:%M:%S")

    # send UDP packet to nodes
    sock.sendto(struct.pack("I", timestamp), ("fec0::2", UDP_TIMESYNC_PORT))
    sock.sendto(struct.pack("I", timestamp), ("fec0::3", UDP_TIMESYNC_PORT))
    
    # sleep for 10 seconds
    time.sleep(10)


# start UDP listener as a thread
t1 = Thread(target=udpListenThread)
t1.start()
print "Listening for incoming packets on UDP port", UDP_REPLY_PORT

time.sleep(1)

# start UDP timesync sender as a thread
t2 = Thread(target=udpSendThread)
t2.start()

print "Sending timesync packets on UDP port", UDP_TIMESYNC_PORT
print "Exit application by pressing (CTRL-C)"

try:
  while True:
    # wait for application to finish (ctrl-c)
    time.sleep(1)
except KeyboardInterrupt:
  print "Keyboard interrupt received. Exiting."
  isRunning = False




