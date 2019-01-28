import sys
import serial
import time
from threading import Thread


ser = serial.Serial('COM7:', 125000)


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
    sys.exit()



while 1:
    line = sys.stdin.readline()

    i = 0
    while i < len(line) - 1:
      ser.write (chr(int(line[i:i+2], 16)))
      print '.'
      i += 2
