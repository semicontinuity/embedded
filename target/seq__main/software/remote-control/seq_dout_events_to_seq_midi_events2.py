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


def main():
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
        event_parts = event.split()
        nibble_n = 2 * int(event_parts[0])
        value = int(event_parts[1])

        b = [0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x04, nibble_n, (value & 0x0f), (value >> 4), 0xf7]
        stdout_print(' '.join(['%02X' % x for x in b]))
        stdout_flush()


if __name__ == "__main__":
    main()
