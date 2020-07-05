# Reads events via serial port of connected I2C-Explorer (obsolete)
import sys
import serial
import time
import threading
from threading import Thread

if len(sys.argv) != 4:
    print "Arguments: <serial port name> <serial port baud rate> <I2C address byte>"
    sys.exit()

port = serial.Serial()
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.timeout = 1.0
port.open()

address_byte_string = sys.argv[3]


class PortReader(Thread):
   def __init__ (self):
      Thread.__init__(self)
      self._stop = threading.Event()
      self._done = threading.Event()
      self._go = threading.Event()

   def exchange(self, s):
      self._result = ''
      port.write(s)
      port.write(chr(13))
      port.write(chr(10))
      self._go.set()
      self._done.wait()
      self._done.clear()
      return self._result

   def run(self):
      while not self.stopped():
        self._go.wait()
        if self.stopped():
           break
        while True:
          c = port.read(1)
          if c == chr(13):
            pass
          elif c == chr(10):
            self._done.set()
            break
          else:
            self._result = self._result + c
        self._go.clear()

   def stop(self):
      self._stop.set()
      self._go.set()

   def stopped(self):
      return self._stop.isSet()


try:
    portReader = PortReader()
    portReader.start()
except (KeyboardInterrupt, SystemExit):
    sys.exit()


class Keyboard:
    def __init__(self):
        init_result = portReader.exchange(c)
        if init_result != 'OK':
            print('Init failed: ' + init_result)
            portReader.stop()
            sys.exit()

    def read(self):
        # Issue I2C read 1 byte
        result = portReader.exchange(address_byte_string + '?' + '01')
        print(result)


try:
    keyboard = Keyboard()
    while True:
        keyboard.read()
finally:
    portReader.stop()
    port.close()
    sys.exit()
