import sys
import serial
import time
from threading import Thread

if len(sys.argv) != 3:
    print "Arguments: <port> <speed>"
    sys.exit(1)

ser = serial.Serial(sys.argv[1], int(sys.argv[2]))


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
        try:
            v = int(line[i:i+2], 16)
            ser.write(chr(v))
            print ">%02X\n" % v
            i += 2
        except (ValueError):
            sys.exit()
