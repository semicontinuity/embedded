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

    def bs_6025(self):
        return b'\x02\x45\x37\x32\x35\x36\x30\x03\x34\x43'

    def f_5010060(self):
        return b'\x02\x46\x35\x30\x31\x30\x30\x30\x36\x30\x03\x44\x35'

    def f_501108006(self):
        return b'\x02\x46\x35\x30\x31\x31\x30\x38\x30\x30\x36\x03\x30\x45'

    def f_7(self):
        return b'\x02\x46\x37\x31\x38\x30\x35\x43\x31\x46\x44\x35\x43\x30\x46\x46\x03\x38\x30'

    def f_50106960(self):
        return b'\x02\x46\x35\x30\x31\x30\x36\x39\x36\x30\x03\x45\x34'

    def write_flash(self):
        return b'\x02\x45\x31\x31\x38\x30\x35\x43\x30\x41\x30\x31\x32\x34\x30\x31\x43\x35\x31\x43\x30\x30\x30\x46\x30\x30\x30\x46\x30\x30\x03\x31\x42'

    def lock_flash(self):
        return b'\x02\x42\x03\x34\x35'

    def bc_6025(self):
        return b'\x02\x45\x38\x37\x36\x36\x30\x03\x35\x33'


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

########################################
time.sleep(0.1)
########################################

s1 = fx3u.bs_6025()
print(s1)
port.write(s1)

########################################
time.sleep(0.1)
########################################

s1 = fx3u.f_5010060()
print(s1)
port.write(s1)

########################################
time.sleep(0.1)
########################################

s1 = fx3u.f_501108006()
print(s1)
port.write(s1)

########################################
time.sleep(0.1)
########################################

s1 = fx3u.f_7()
print(s1)
port.write(s1)

########################################
time.sleep(0.1)
########################################

s1 = fx3u.f_50106960()
print(s1)
port.write(s1)

########################################
time.sleep(1)
########################################

s1 = fx3u.write_flash()
print(s1)
port.write(s1)

########################################
time.sleep(0.4)
########################################

s1 = fx3u.lock_flash()
print(s1)
port.write(s1)

########################################
time.sleep(0.4)
########################################

s1 = fx3u.bc_6025()
print(s1)
port.write(s1)

sys.stdin.readline()
portReader.stop()
sys.exit()

