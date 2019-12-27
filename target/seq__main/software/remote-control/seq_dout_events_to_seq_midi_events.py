#!/usr/bin/env python3
import sys
import json

import mido
import sys


def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


def run(outport):
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
        event_parts = event.split()
        nibble_n = 2 * int(event_parts[0])
        value = int(event_parts[1])

        b = [0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x04, nibble_n, (value & 0x0f), (value >> 4), 0xf7]
        #stderr_print(b)
        m = mido.parse(b)
        outport.send(m)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)

