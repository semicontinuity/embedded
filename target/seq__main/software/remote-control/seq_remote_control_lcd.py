#!/usr/bin/env python3
#################################################################################
# Renders text on LCD of SEQ in Client mode
#################################################################################
import mido
import sys
import time

def run(port):

  counter = 0

  while True:
    # remote client on - repeated, otherwise Client mode will be terminated in 5s
    m = mido.parse([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x00, 0x02, 0xf7])
    print(m)
    port.send(m)

    text = 'Counter: ' + str(counter)

    # render text on LCD
    cmd = bytearray([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x02, 16, 0x00]) + bytearray(text, 'utf8') + bytearray([0xf7])
    m = mido.parse(cmd)
    print(m)
    port.send(m)

    time.sleep(1)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)
