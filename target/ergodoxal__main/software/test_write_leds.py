#!/usr/bin/env python3
import sys
import serial

if len(sys.argv) != 4:
    print("Please supply COM port name and speed + hex LED values")
    sys.exit()


d = [int(c, 16) for c in sys.argv[3]]
b = []
n_bytes = len(d) // 2
for i in range(n_bytes):
  b.append(16*d[2*i] + d[2*i + 1])

b.reverse()

port = serial.Serial(sys.argv[1], int(sys.argv[2]))
port.write(b)

print(b)