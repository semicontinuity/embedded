#!/usr/bin/env python3.8
import mido
import sys
import serial


def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit("Arguments: <MIDI IN port name> <USB-Serial device>")

    port = serial.Serial(sys.argv[2], 115200)

    with mido.open_input(sys.argv[1]) as inport:
        for msg in inport:
          b = msg.bytes()
          if b[2] == 0x7f:
            port.write(bytes([10]))
