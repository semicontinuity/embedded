import sys
if len(sys.argv) != 4:
    print "Arguments: <port> <speed> <hex code>"
    sys.exit(1)

import serial
ser = serial.Serial(sys.argv[1], int(sys.argv[2]))

value = int(
from threading import Thread
class PortReader(Thread):

   def __init__ (self):
      Thread.__init__(self)

   def run(self):
      while 1:
        while ser.inWaiting() > 0:
          c = ser.read(1)
          print "%02X " % ord(c)

try:
    portReader = PortReader()
    portReader.start()
except (KeyboardInterrupt, SystemExit):
    sys.exit(2)


ser.write(chr((0xC0 | self.value)))
