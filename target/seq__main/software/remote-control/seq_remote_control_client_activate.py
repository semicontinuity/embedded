#!/usr/bin/env python3
#################################################################################
# Sends command REMOTE MODE=CLIENT.
# (Must be repeated, otherwise Client mode will be terminated in 5s on timeout)
#################################################################################

import mido
import sys
import time

def main(port):

  # Client mode
  m = mido.parse([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x00, 0x02, 0xf7])
  port.send(m)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)
