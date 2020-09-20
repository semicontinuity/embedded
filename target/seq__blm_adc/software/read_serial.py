#!/usr/bin/env python

import sys
import serial
import time
import threading
from threading import Thread

if len(sys.argv) != 3:
    print "Please supply COM port name and speed"
    sys.exit()

print sys.argv[1]
#port = serial.Serial(sys.argv[1], int(sys.argv[2]))
port = serial.Serial()
#port.dsrdtr=False
#port.setDTR(level=0)
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.timeout=1

#port.setDTR(0)
#port.setDTR(False)
#port.setDTR(level=False)
#time.sleep(0.5)
port.open()

#time.sleep(0.5)


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

    sys.stdin.readline()
    portReader.stop()
    sys.exit()

except (KeyboardInterrupt, SystemExit):
    sys.exit()

