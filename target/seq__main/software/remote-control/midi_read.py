#!/usr/bin/env python3
import mido
import sys


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI IN port name'")

    with mido.open_input(sys.argv[1]) as inport:
        for msg in inport:
            print(msg)
