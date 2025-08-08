#!/usr/bin/env python3

import sys
import threading
import time
from threading import Thread

import serial


class PortReader(Thread):

   def __init__ (self, port):
      Thread.__init__(self)
      self._port = port
      self._stop = threading.Event()

   def run(self):
      while not self.stopped():
        while self._port.inWaiting() > 0:
          c = self._port.read(1)
          print("%02X " % ord(c))

   def stop(self):
      self._stop.set()

   def stopped(self):
      return self._stop.is_set()


class Fx3u:
    def __init__(self, station_no: int = 1, wait_time: int = 3):
        self.station_no = station_no
        self.wait_time = wait_time

    def enq(self):
        data = bytearray(1)
        data[0] = 0x05
        return data

    def bit_clear(self):
        return b'\x02\x45\x38\x30\x33\x35\x45\x03\x35\x44'


port = serial.Serial(
    "/dev/ttyUSB0",
    baudrate=38400,
    bytesize=7,
    parity=serial.PARITY_EVEN
)


try:
    portReader = PortReader(port)
    portReader.start()
except (KeyboardInterrupt, SystemExit):
    sys.exit()


fx3u = Fx3u()


s = fx3u.enq()
print(s)
port.write(s)

time.sleep(0.1)

s1 = fx3u.bit_clear()
print(s1)
port.write(s1)

sys.stdin.readline()
portReader.stop()
sys.exit()

