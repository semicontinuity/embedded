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


def hex(n: int):
    return 0x30 + n if n < 10 else 0x41 + n - 10


def lo_nibble(n: int):
    return n & 0x0F


def hi_nibble(n: int):
    return (n >> 4) & 0x0F


class Fx3u:
    def __init__(self, station_no: int = 1, plc_no: int = 0xFF, wait_time: int = 3, sum_check = False, cr_lf = False):
        self.station_no = station_no
        self.plc_no = plc_no
        self.wait_time = wait_time
        self.sum_check = sum_check
        self.cr_lf = cr_lf

    def _cmd_header(self, data, cmd_lo, cmd_hi):
        data[0] = 0x05
        data[1] = hex(hi_nibble(self.station_no))
        data[2] = hex(lo_nibble(self.station_no))
        data[3] = hex(hi_nibble(self.plc_no))
        data[4] = hex(lo_nibble(self.plc_no))
        data[5] = ord(cmd_lo)
        data[6] = ord(cmd_hi)
        data[7] = hex(self.wait_time)
        return 8

    def _cmd_footer(self, data, i):
        if self.sum_check:
            data[i] = 0x00
            i += 1
            data[i] = 0x00
            i += 1

        if self.cr_lf:
            data[i] = 0x0D
            i += 1
            data[i] = 0x0A
            i += 1

    def _data_append(self, data, i, b):
        data[i] = b
        i += 1
        return i

    def cmd_loopback_test(self, text: bytes):
        data = bytearray(10 + len(text) + (2 if self.sum_check else 0) + (2 if self.cr_lf else 0))
        self._cmd_header(data, 'T', 'T')
        data[8] = hex(hi_nibble(len(text)))
        data[9] = hex(lo_nibble(len(text)))

        i = 10
        for b in text:
            data[i] = b
            i += 1

        self._cmd_footer(data, i)
        return data

    def cmd_batch_read_bits(self):
        data = bytearray(8 + 6 + (2 if self.sum_check else 0) + (2 if self.cr_lf else 0))
        i = self._cmd_header(data, 'B', 'R')
        i = self._data_append(data, i, ord('Y'))
        i = self._data_append(data, i, ord('0'))
        i = self._data_append(data, i, ord('0'))
        i = self._data_append(data, i, ord('0'))

        i = self._data_append(data, i, ord('0'))
        i = self._data_append(data, i, ord('4'))

        self._cmd_footer(data, i)
        return data


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


#s = fx3u.cmd_loopback_test(b'ABCD')
s = fx3u.cmd_batch_read_bits()
print(s)

#port.write(b'\0x05\x0D\x0A')
#time.sleep(0.1)

port.write(s)

time.sleep(1)

port.write(s)


sys.stdin.readline()
portReader.stop()
sys.exit()

