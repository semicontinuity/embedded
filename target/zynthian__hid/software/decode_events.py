#!/usr/bin/env python3
import sys
import time
from threading import Thread, Event

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

            event = int(line.strip(), 16)
            is_button = event & 0x80
            if is_button:
                pressed = event & 0x01
                button = (event & 0x7F) >> 1
                stdout_print(0x04 | button, 1 if pressed else -1, sep='\t')
            else:
                delta_bits = event & 0x1F
                encoder = event >> 5
                stdout_print(encoder, delta_bits if delta_bits < 16 else delta_bits - 32, sep='\t')
            stdout_flush()

if __name__ == "__main__":
    main()
