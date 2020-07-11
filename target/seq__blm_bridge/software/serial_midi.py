#!/usr/bin/env python3
##################################################################
# serial midi -> stdout -> prints MIDI messages as HEX bytes
# HEX bytes   -> stdin  -> serial midi
#
# ONLY CHANNEL MESSAGES are supported
##################################################################
import sys
import serial
import time
import threading
from threading import Thread

if len(sys.argv) != 3:
    print("Please supply COM port name and speed")
    sys.exit()

port = serial.Serial()
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.timeout=1
port.open()


class PortReader(Thread):

   def __init__ (self):
      Thread.__init__(self)
      self._stop = threading.Event()

   def run(self):
      buffer = []
      while not self.stopped():
        while port.inWaiting() > 0:
          c = port.read(1)[0]

          # out-of-order non-status byte flushes
          if len(buffer) == 0 and c < 0x80:
              print(" ".join(["%02X" % c for c in buffer]))
              print("%02X" % c)
              buffer.clear()
              continue

          buffer.append(c)

          # 2-byte Cx and Dx messages
          if len(buffer) == 2 and ((buffer[0] & 0xC0) == 0xC0):
              print(" ".join(["%02X" % c for c in buffer]))
              buffer.clear()
              continue

          # other channel messages have length 3 bytes
          if len(buffer) == 3:
              print(" ".join(["%02X" % c for c in buffer]))
              buffer.clear()
              continue


   def stop(self):
      self._stop.set()

   def stopped(self):
      return self._stop.isSet()



portReader = PortReader()
portReader.start()

try:
    while True:
        line = sys.stdin.readline()
        if not line: break

        l = line.strip()
        hex_digits = l.split(' ')
        bytes = [int(d, 16) for d in hex_digits]
        port.write(bytes)
finally:
    portReader.stop()

