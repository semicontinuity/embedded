# Test the serial CAN adapter.
# CAN adapter responds to messages having HOST field set to 0.
# Test by reading the adapter memory using PROTOCOL_CMD_READ_MEM

import serial

port = serial.Serial('COM7:', 125000)

PROTOCOL_CMD_READ_MEM = 0
ADAPTER_QUERY = 0
ADDRESS_L = 8
ADDRESS_H = 8

# Issue PROTOCOL_CMD_READ_MEM

port.write(chr(PROTOCOL_CMD_READ_MEM))
port.write(chr(0))
port.write(chr(ADAPTER_QUERY))
port.write(chr(0))
port.write(chr(0))

port.write(chr(ADDRESS_L))
port.write(chr(ADDRESS_H))
port.write(chr(0))
port.write(chr(0))
port.write(chr(0))
port.write(chr(0))
port.write(chr(0))
port.write(chr(0))

# Read response packet
r00 = port.read()
r01 = port.read()
r02 = port.read()
r03 = port.read()
r04 = port.read()
print "%02X %02X %02X %02X %02X" % (ord(r00), ord(r01), ord(r02), ord(r03), ord(r04))

r05 = port.read()
r06 = port.read()
r07 = port.read()
r08 = port.read()
r09 = port.read()
r0A = port.read()
r0B = port.read()
r0C = port.read()
print "%02X %02X %02X %02X %02X %02X %02X %02X" % (ord(r05), ord(r06), ord(r07), ord(r08), ord(r09), ord(r0A), ord(r0B), ord(r0C))
