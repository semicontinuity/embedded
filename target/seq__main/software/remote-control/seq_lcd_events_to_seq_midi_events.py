#!/usr/bin/env python3

################################################
# STDIN: LCD events, one per line, in TSV format
# X<tab>Y<tab>TEXT
#
# STDOUT: MIDI messages in hex format, like
# F0 00 00 7E ...
################################################

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

        event_parts = line.split('\t')
        x = int(event_parts[0])
        y = int(event_parts[1])
        text = event_parts[2][:-1]

        cmd = bytearray([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x02, x, y]) + bytearray(text, 'utf8') + bytearray([0xf7])
        stdout_print(' '.join(['%02X' % x for x in cmd]))
        stdout_flush()

if __name__ == "__main__":
    main()

