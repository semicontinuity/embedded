#!/usr/bin/env python3.8
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
          b = msg.bytes()
          lsb = b[1]
          msb = b[2]
          reading = (msb << 7) + lsb

          if msg.channel == 1:
            rh = (reading / (1 << 14)) * 100.0
            print("RH", rh)
          else:
            t = (reading / (1 << 14)) * 200.0 - 50.0
            print("T", t)
