#!/usr/bin/env python3

import mido
import sys


def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def stderr_flush():
    sys.stderr.flush()


def run(port):
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
#        stdout_print(event, end='')

        hex_numbers = event.split(" ")
        payload = [int(i, 16) for i in hex_numbers]
        port.send(mido.parse(payload))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)
