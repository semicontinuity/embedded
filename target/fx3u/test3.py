#!/usr/bin/env python3

# Request:
#  [ENQ]            1    05H
#
# ...
#  02|30 30 45 30 32 30 32|03|36 43
#
# expect: 02|42 31 35 45|03|46 30

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
      return self._stop.isSet()


class Fx3u:
    def __init__(self, station_no: int = 1, plc_no: int = 0xFF, wait_time: int = 3, sum_check = False, cr_lf = False):
        self.station_no = station_no
        self.wait_time = wait_time

    def enq(self):
        data = bytearray(1)
        data[0] = 0x05
        return data

    def hello(self):
        return b'\x02\x30\x30\x45\x30\x32\x30\x32\x03\x36\x43'


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

s1 = fx3u.hello()
print(s1)
port.write(s1)

sys.stdin.readline()
portReader.stop()
sys.exit()

