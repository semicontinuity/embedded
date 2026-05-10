# Test writing of Holding Register.

import sys
import serial
import time
import threading
from threading import Thread
from crc16 import crc16

if len(sys.argv) != 5:
    print "Please supply COM port name and speed, holding register number, holding register value"
    sys.exit()

register_number = int(sys.argv[3])
if register_number < 0 or register_number > 255:
    print "Invaild holding register number"
    sys.exit()

register_value = int(sys.argv[4])
if register_value <= 0 or register_value > 255:
    print "Invaild holding register value"
    sys.exit()

port = serial.Serial()
port.dsrdtr=False
port.setDTR(level=0)
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.timeout=1
time.sleep(0.5)
port.open()

#time.sleep(5)
#print ">"

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
MF_WRITE_REGISTER = 6


data = bytearray(8)
data[0] = SLAVE_ADDRESS
data[1] = MF_WRITE_REGISTER
data[2] = register_number >> 8
data[3] = register_number & 0xFF
data[4] = register_value >> 8
data[5] = register_value & 0xFF

crc = crc16(0xFFFF, data, 6)

data[6] = crc & 0xFF
data[7] = crc >> 8
port.write(data)

sys.stdin.readline()
portReader.stop()
sys.exit()
