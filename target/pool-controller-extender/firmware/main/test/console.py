import sys
import serial
import time
from threading import Thread
from threading import Event

if len(sys.argv) != 3:
    print "Arguments: <port> <speed>"
    sys.exit(1)

ser = serial.Serial(sys.argv[1], int(sys.argv[2]))


class PortReader(Thread):

   def __init__ (self):
      Thread.__init__(self)
      self._stop = Event()

   def run(self):
      while not self.stopped():
        while ser.inWaiting() > 0:
          c = ser.read(1)
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
            portReader.stop()
            sys.exit()
