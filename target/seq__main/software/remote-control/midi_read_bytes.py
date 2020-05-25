#!/usr/bin/env python3
import mido
import sys


def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI IN port name'")

    with mido.open_input(sys.argv[1]) as inport:
        for msg in inport:
            stdout_print(" ".join("%02X" % i for i in msg.bytes()))
            stdout_flush()
