# Test reading of Holding Register.
# Frame format: [Slave Address][Function][16-bit first register][16-bit number of registers][16-bit CRC]

import sys
import serial
import time
import threading
from threading import Thread

if len(sys.argv) != 3:
    print "Please supply COM port name and speed"
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
MF_READ_HOLDING_REGISTER = 3


port.write(chr(SLAVE_ADDRESS))
port.write(chr(MF_READ_HOLDING_REGISTER))

port.write(chr(0))
port.write(chr(0))

port.write(chr(0))
port.write(chr(4))

port.write(chr(0x44))
port.write(chr(0x09))

sys.stdin.readline()
portReader.stop()
sys.exit()
