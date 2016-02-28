import sys
import serial
import time
import threading
from threading import Thread

if len(sys.argv) != 6:
    print "Arguments: <COM port name> <speed> <type=c801|c256|c1001> <operation=read|program> <file>"
    sys.exit()

eprom_type = sys.argv[3]
operation = sys.argv[4]
file_name = sys.argv[5]

port = serial.Serial()
port.port = sys.argv[1]
port.baudrate = int(sys.argv[2])
port.open()


class PortReader(Thread):
   def __init__ (self):
      Thread.__init__(self)
      self._stop = threading.Event()
      self._done = threading.Event()

   def exchange(self, s):
#      print s
      self._result = ''
      port.write(s)
      port.write(chr(10))
      self._done.wait()
      self._done.clear()
      return self._result

   def run(self):
      while not self.stopped():
        while port.inWaiting() > 0:
          c = port.read(1)
#          print ord(c)
          if c == chr(10):
            self._done.set()
          else:
#            print c
            self._result = self._result + c

   def stop(self):
      self._stop.set()

   def stopped(self):
      return self._stop.isSet()



try:
    portReader = PortReader()
    portReader.start()
except (KeyboardInterrupt, SystemExit):
    sys.exit()



class EPROM:
    def __init__(self):
        self.mode_output(self.pin_CE())
        self.pin_high(self.pin_CE())
        if self.pin_G():
            self.mode_output(self.pin_G())
            self.pin_high(self.pin_G())
        if self.pin_P():
            self.mode_output(self.pin_P())
            self.pin_high(self.pin_P())
        self.mode_output(self.pins_A0_A7_port())
        self.mode_output(self.pins_A8_A15_port())
        if (self.pin_A16()):
            self.mode_output(self.pin_A16())
        if (self.pin_A17()):
            self.mode_output(self.pin_A17())
        if (self.pin_A18()):
            self.mode_output(self.pin_A18())
        if (self.pin_A19()):
            self.mode_output(self.pin_A19())

    def size(self):
        return None

    def command(self, c):
        result = portReader.exchange(c)
        if result != 'OK':
            print 'Command ' + c + ' failed: returned ' + result
            portReader.stop()
            sys.exit()

    def mode_output(self, port):
        self.command(port + 'W')

    def mode_input(self, port):
        self.command(port + 'R')

    def port_set(self, port, value):
        self.command(port + '=' + ("%02X" % value))

    def port_get(self, port):
        result = portReader.exchange(port)
        try:
            return int(result, 16)
        except:
            print 'Reading port ' + port + ' failed: returned ' + result
            portReader.stop()
            sys.exit()            

    def pin_set(self, pin, value):
        self.command(pin + '=' + str(value))

    def pin_high(self, pin):
        self.pin_set(pin, 1)

    def pin_low(self, pin):
        self.pin_set(pin, 0)

    def pin_CE(self):
        return 'D3'

    def pin_PROG(self):
        return 'D2'

    def pin_G(self):
        return None

    def pin_P(self):
        return None

    def program_strobe(self):
        if self.pin_P():
            self.pin_low(self.pin_P())
            self.pin_high(self.pin_P())
        else:
            self.enable()
            self.disable()

    def enable(self):
        self.pin_low(self.pin_CE())

    def enable_bus_drive(self):
        # If pin G is not present, bus will be driven (read mode) when programming is not enabled
        if self.pin_G():
            self.pin_low(self.pin_G())

    def enable_programming_voltage(self):
        self.pin_high(self.pin_PROG())

    def disable_programming_voltage(self):
        self.pin_low(self.pin_PROG())

    def disable(self):
        self.pin_high(self.pin_CE())

    def disable_bus_drive(self):
        # If pin G is not present, bus will be driven (read mode) when programming is not enabled 
        if self.pin_G():
            self.pin_high(self.pin_G())

    def in_read_mode(self, f):
        eprom.enable_bus_drive()
        eprom.enable()
        result = f()
        eprom.disable()
        eprom.disable_bus_drive()
        return result

    def in_program_mode(self, f):
        self.enable_programming_voltage()
        self.data_bus_mode_output()
        if self.pin_P():
            self.enable()
        result = f()
        if self.pin_P():
            self.disable()
        self.data_bus_mode_input()
        self.disable_programming_voltage()
        return result

    def pin_G(self):
        return None

    def pins_Q0_Q7_port(self):
        return 'C'

    def pins_A0_A7_port(self):
        return 'A'

    def pins_A8_A15_port(self):
        return 'B'

    def pin_A16(self):
        return None

    def pin_A17(self):
        return None

    def pin_A18(self):
        return None

    def pin_A19(self):
        return None

    def data_bus_mode_input(self):
        self.mode_input(self.pins_Q0_Q7_port())

    def data_bus_mode_output(self):
        self.mode_output(self.pins_Q0_Q7_port())

    def data_bus_get(self):
        return self.port_get(self.pins_Q0_Q7_port())

    def data_bus_set(self, value):
        self.port_set(self.pins_Q0_Q7_port(), value)

    def set_address_bits_0_7(self, value):
        self.port_set(self.pins_A0_A7_port(), value)

    def set_address_bits_8_15(self, value):
        self.port_set(self.pins_A8_A15_port(), value)

    def set_address_bits_8plus(self, value):
        self.set_address_bits_8_15((value >> 8) & 0xFF)
        if self.pin_A16():
            self.pin_set(self.pin_A16(), 1 if value & 0x00010000 else 0)
        if self.pin_A17():
            self.pin_set(self.pin_A17(), 1 if value & 0x00020000 else 0)
        if self.pin_A18():
            self.pin_set(self.pin_A18(), 1 if value & 0x00040000 else 0)
        if self.pin_A19():
            self.pin_set(self.pin_A19(), 1 if value & 0x00080000 else 0)

    def read_256_byte_chunk(self, c):
        print 'read chunk %04X' % c
        self.set_address_bits_8plus(c << 8)
        result = bytearray(256)
        for b in range(0, 256):
            self.set_address_bits_0_7(b)
            result[b] = self.data_bus_get()
        return result

    def write_256_byte_chunk(self, c, data):
        print 'write chunk %04X' % c
        self.set_address_bits_8plus(c << 8)
        for b in range(0, 256):
            if ord(data[b]) != 0xFF:
                self.set_address_bits_0_7(b)
                self.data_bus_set(ord(data[b]))
                self.program_strobe()




class M27C256(EPROM):
    def __init__(self):
        EPROM.__init__(self)

    def size(self):
        return 0x8000

    def pin_G(self):
        return 'D7'



class M27C801(EPROM):
    def __init__(self):
        EPROM.__init__(self)

    def size(self):
        return 0x100000

    def pin_A16(self):
        return 'D4'

    def pin_A17(self):
        return 'D5'

    def pin_A18(self):
        return 'D6'

    def pin_A19(self):
        return 'D7'



class M27C1001(EPROM):
    def __init__(self):
        EPROM.__init__(self)

    def size(self):
        return 0x20000

    def pin_A16(self):
        return 'D4'

    def pin_P(self):
        return 'D6'
      


if eprom_type == 'c801':
    eprom = M27C801()
elif eprom_type == 'c256':
    eprom = M27C256()
elif eprom_type == 'c1001':
    eprom = M27C1001()
else:
    print 'Unknown EPROM type: ' + eprom_type
    portReader.stop()
    sys.exit()


if operation == 'read':
    f = open(file_name, "wb")
    for c in range(0, eprom.size() / 256):
        chunk = eprom.in_read_mode(lambda: eprom.read_256_byte_chunk(c))
        f.write(chunk)
    f.close
elif operation == 'program':
    data = open(file_name, "rb").read()
    for c in range(0, eprom.size() / 256):
        chunk = data[c*256: (c+1)*256]
        eprom.in_program_mode(lambda: eprom.write_256_byte_chunk(c, chunk))
else:
    print 'Unknown operation: ' + operation
    portReader.stop()
    sys.exit()


portReader.stop()
sys.exit()
