#!/usr/bin/env python

from __future__ import print_function
import sys
import serial
import time
import threading
from threading import Thread


def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)


def stdout_flush():
    sys.stdout.flush()


def trace(*args, **kwargs):
    print(*args, file=sys.stderr, sep='\t', **kwargs)


def info(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


class PortReader(Thread):
   def __init__ (self, port):
      Thread.__init__(self)
      self.port = port
      self._stop = threading.Event()
      self._done = threading.Event()
      self._go = threading.Event()

   def exchange(self, s):
      self._result = ''
      port.write(s)
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
          if c == chr(10):
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


class I2CBridge:
    def __init__(self, port_reader):
        self.port_reader = port_reader

    def command(self, c):
        # print('Sending', c)
        result = self.port_reader.exchange(c).strip()
        if result.strip() == 'ERROR':
            info('Command ' + c + ' failed: returned [' + result + ']')
        else:
            return result

    def init_speed(self):
        self.command('')
        self.command('I1')

    def read_event(self):
        event_str = self.command('%02X?01' % ((0x08) * 2))
        if event_str:
            event = int(event_str, 16)
            return event if event !=0 else None


def run(port):
    port_reader = PortReader(port)
    port_reader.start()
    i2c_bridge = I2CBridge(port_reader)

    try:
        while True:
            line = i2c_bridge.read_event()
            if line:
                print(line)
    finally:
        port_reader.stop()


if __name__ == "__main__":
    if len(sys.argv) != 3:
        info("Arguments: <COM port name> <speed>")
        sys.exit()

    port = serial.Serial()
    port.port = sys.argv[1]
    port.baudrate = int(sys.argv[2])
    port.timeout = 1.0
    port.open()

    try:
        run(port)
    finally:
        port.close()
        sys.exit()
