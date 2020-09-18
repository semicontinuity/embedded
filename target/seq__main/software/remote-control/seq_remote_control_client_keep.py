#!/usr/bin/env python3
#################################################################################
# Repeatedly sends command REMOTE MODE=CLIENT.
# (Must be repeated, otherwise Client mode will be terminated in 5s on timeout)
#################################################################################

import mido
import sys
import time

def text(port, x, y, text):
  cmd = bytearray([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x02, x, y]) + bytearray(text, 'utf8') + bytearray([0xf7])
  m = mido.parse(cmd)
  port.send(m)

def run(port):

  # Client mode
  m = mido.parse([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x00, 0x02, 0xf7])
  port.send(m)

  text(port, 0, 0, ' '*20)
  text(port, 20, 0, ' '*20)

  while True:
    m = mido.parse([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x00, 0x02, 0xf7])
    port.send(m)

    time.sleep(1)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)
