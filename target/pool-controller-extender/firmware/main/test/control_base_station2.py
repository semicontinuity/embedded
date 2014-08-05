# Reads keyboard and simulates appropriate events that are sent over serial port to the extender,
# to simulate key presses on the pool control station.
#
# Supported keys:
#
# UP      simulates press of UP key on the pool control station
# DOWN    simulates press of DOWN key on the pool control station
# ENTER   simulates press of ENTER key on the pool control station
# ESCAPE  simulates press of ESCAPE key on the pool control station
# LEFT    simulates press of LEFT key on the pool control station
# RIGHT   simulates press of RIGHT key on the pool control station

# BACKSPACE simulates LONG press of ESCAPE key on the pool control station (turn on/turn off)


MASK_KEY_ENTER	= 0b00000001
MASK_KEY_ESCAPE	= 0b00000010
MASK_KEY_RIGHT	= 0b00000100
MASK_KEY_LEFT	= 0b00001000
MASK_KEY_DOWN	= 0b00010000
MASK_KEY_UP	= 0b00100000

import sys
if len(sys.argv) != 3 and len(sys.argv) != 4:
    print "Arguments: <port> <speed> [keypress delay]"
    sys.exit(1)

import serial
ser = serial.Serial(sys.argv[1], int(sys.argv[2]))

DELAY = 0.2 if len(sys.argv) == 3 else float(sys.argv[3])


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



import time
class SimulateKey(Thread):

   def __init__ (self, value, delay):
      Thread.__init__(self)
      self.value = value
      self.delay = delay

   def run(self):
      print ">"
      print "%02X " % self.value
      ser.write(chr(self.value))
      #time.sleep(0.001)      
      print "%02X " % (0xC0 | self.value)
      ser.write(chr((0xC0 | self.value)))

      time.sleep(self.delay)
      
      print "%02X " % 0x00
      ser.write(chr(0x00))
      #time.sleep(0.001)      
      print "%02X " % (0xC0 | 0x00)
      ser.write(chr((0xC0 | 0x00)))


import msvcrt as m

def up():
    SimulateKey(MASK_KEY_UP, DELAY).start()

def down():
    SimulateKey(MASK_KEY_DOWN, DELAY).start()

def left():
    SimulateKey(MASK_KEY_LEFT, DELAY).start()

def right():
    SimulateKey(MASK_KEY_RIGHT, DELAY).start()

def escape():
    SimulateKey(MASK_KEY_ESCAPE, DELAY).start()

def enter():
    SimulateKey(MASK_KEY_ENTER, DELAY).start()

def backspace():
    SimulateKey(MASK_KEY_ESCAPE, 6).start()


while True:
    c1 = ord(m.getch())
    if c1 == 224:
        c2 = ord(m.getch())
        if c2 == 72:
            up()
        elif c2 == 80:
            down()
        elif c2 == 77:
            right()
        elif c2 == 75:
            left()
    elif c1 == 27:
        escape()
    elif c1 == 13:
        enter()
    elif c1 == 8:
        backspace()
