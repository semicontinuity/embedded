#!/usr/bin/env python3

import sys
import serial
import time
import threading
from threading import Thread

if len(sys.argv) != 3:
    print("Please supply COM port name and speed (/dev/ttyUSB0 38400)", file=sys.stderr)
    sys.exit()

port = serial.Serial()
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.timeout=1
port.open()


def bit_s(n, value):
   return "#" if (value & (1 << n)) != 0 else "-"


class PortReader(Thread):

   def __init__ (self):
      Thread.__init__(self)
      self._stop = threading.Event()

   def run(self):
      while not self.stopped():
        while port.inWaiting() > 0:
          code = ord(port.read(1))
          print("%02x\t%s%s%s%s:%s%s%s%s" % (code, bit_s(7, code), bit_s(6, code), bit_s(5, code), bit_s(4, code), bit_s(3, code), bit_s(2, code), bit_s(1, code), bit_s(0, code)))

   def stop(self):
      self._stop.set()

   def stopped(self):
      return self._stop.isSet()


try:
    portReader = PortReader()
    portReader.start()

    sys.stdin.readline()
    portReader.stop()
    sys.exit()

except (KeyboardInterrupt, SystemExit):
    sys.exit()

