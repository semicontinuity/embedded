# Test READ_COLIS unction.

import sys
import serial
import time
import threading
from threading import Thread
from crc16 import crc16

if len(sys.argv) != 5:
    print "Please supply COM port name and speed, starting coil number, coil count"
    sys.exit()

coil_number = int(sys.argv[3])
if coil_number < 0 or coil_number > 255:
    print "Invalid coil number"
    sys.exit()

coil_count = int(sys.argv[4])
if coil_count <= 0 or coil_count > 255:
    print "Invalid coil count"
    sys.exit()

port = serial.Serial()
port.dsrdtr=False
port.setDTR(0)
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.timeout=1
time.sleep(0.5)
port.open()


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



SLAVE_ADDRESS = 2
MF_READ_COILS = 1


data = bytearray(8)
data[0] = SLAVE_ADDRESS
data[1] = MF_READ_COILS
data[2] = coil_number >> 8
data[3] = coil_number & 0xFF
data[4] = coil_count >> 8
data[5] = coil_count & 0xFF

crc = crc16(0xFFFF, data, 6)

data[6] = crc & 0xFF
data[7] = crc >> 8

#data[6] = 0x44
#data[7] = 0x09
port.write(data)
print data

sys.stdin.readline()
portReader.stop()
sys.exit()
