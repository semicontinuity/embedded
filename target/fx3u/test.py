#!/usr/bin/env python3

# Protocol:
#   https://dl.mitsubishielectric.com/dl/fa/document/manual/plc_fx/jy992d69901/jy992d69901e.pdf
#   chapter 7
#
# Request:
#  [ENQ]            1    05H
#  [Station No]     2
#  [PLC No]         2
#  [Command]        2
#  [Msg wait time]  1
#  [Char area]      ?
#  [Sum check code] 0/2
#
# Request example:
#  [ENQ]                  05H
#  [Station No]     00    30H 30H
#  [PLC No]         FF    46H 46H
#  [Command]        BR    42H 52H
#  [Msg wait time]  03    33H
#  [Char area]      ABCD  41H 42H 43H 44H
#  [Sum check code] BD    42H 44H (Sum=2BDH)


import sys
import serial
import time
import threading
from threading import Thread
from crc16 import crc16


#if len(sys.argv) != 3:
#    print "Please supply COM port name and speed"
#    sys.exit()


#print sys.argv[1]
#port = serial.Serial(sys.argv[1], int(sys.argv[2]))


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



#try:
#    portReader = PortReader()
#    portReader.start()
#except (KeyboardInterrupt, SystemExit):
#    sys.exit()


def hex(n: int):
    return 0x30 + n if n < 10 else 0x41 + n - 10


def lo_nibble(n: int):
    return n & 0x0F


def hi_nibble(n: int):
    return (n >> 4) & 0x0F


class Fx3u:
    def __init__(self, station_no: int = 1, plc_no: int = 0xFF, wait_time: int = 3):
        self.station_no = station_no
        self.plc_no = plc_no
        self.wait_time = wait_time

    def cmd_loopback_test(self, text: bytes):
        data = bytearray(10 + len(text))
        data[0] = 0x05
        data[1] = hex(hi_nibble(self.station_no))
        data[2] = hex(lo_nibble(self.station_no))
        data[3] = hex(hi_nibble(self.plc_no))
        data[4] = hex(lo_nibble(self.plc_no))
        data[5] = ord('T')
        data[6] = ord('T')
        data[7] = hex(self.wait_time)
        data[8] = hex(hi_nibble(len(text)))
        data[9] = hex(lo_nibble(len(text)))

        i = 10
        for b in text:
            data[i] = b
            i += 1

        return data


#port.write(data)


#sys.stdin.readline()
#portReader.stop()
#sys.exit()


fx3u = Fx3u()
s = fx3u.cmd_loopback_test(b'ABCD')
print(s)
