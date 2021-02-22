#!/usr/bin/env python3

################################################
# STDIN: LED events, one per line, in TSV format
# ON/OFF<tab>LED_NAME
#
# STDOUT: MIDI messages in hex format, like
# F0 00 00 7E ...
################################################

import sys
import json

dout = [0] * 28


def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def with_tabs(s):
    return '\t'.join(s.split())


def run(mapping):
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
        event_parts = event.split()
        on_off = event_parts[0] == 'ON'
        led = event_parts[1]

        dout_pos = mapping.get(led)
        if dout_pos is None:
            continue

        sr = dout_pos[0]
        bit = dout_pos[1]
        mask = 1 << bit

        if on_off:
            dout[sr] |= mask
        else:
            dout[sr] &= ~mask

        stdout_print(sr, dout[sr])
        stdout_flush()


def main():
    if len(sys.argv) < 2:
        sys.exit("Argument: 'json-with-mapping'")

    mapping = json.loads(sys.argv[1])
    run(mapping)


if __name__ == "__main__":
    main()
