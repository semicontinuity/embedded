# Test reading of Holding Register.
# Frame format: [Slave Address][Function][16-bit first register][16-bit number of registers][16-bit CRC]

import sys
import serial
import time
import threading
from threading import Thread
from crc16 import crc16

if len(sys.argv) != 5:
    print "Please supply COM port name and speed, coil number, coil value"
    sys.exit()

print sys.argv[1]
port = serial.Serial(sys.argv[1], int(sys.argv[2]))

class PortReader(Thread):

   def __init__ (self):
      Thread.__init__(self)
      self._stop = threading.Event()

   def run(self):
      while not self.stopped():
        while port.inWaiting() > 0:
          c = port.read(1)
          print "%02X " % ord(c)

   def stop(self):
      self._stop.set()

   def stopped(self):
      return self._stop.isSet()



try:
    portReader = PortReader()
    portReader.start()
except (KeyboardInterrupt, SystemExit):
    sys.exit()



SLAVE_ADDRESS = 1
MF_WRITE_SINGLE_COIL = 5

coil_address = int(sys.argv[3])
if coil_address < 0 or coil_address >= 4:
    print "Invaild coil address"
    sys.exit()

coil_value = int(sys.argv[4])

data = bytearray(8)
data[0] = SLAVE_ADDRESS
data[1] = MF_WRITE_SINGLE_COIL
data[2] = coil_address
data[3] = 0
data[4] = 0x00
data[5] = 0x00 if coil_value == 0 else 0xFF

crc = crc16(0xFFFF, data, 6)

data[6] = crc & 0xFF
data[7] = crc >> 8
port.write(data)

sys.stdin.readline()
portReader.stop()
sys.exit()
