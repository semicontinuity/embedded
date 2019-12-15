#!/usr/bin/env python3
import mido
import sys


def run(port):
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip();
        parts = event.split();
        if parts[0] == 'note_on':
            m = mido.Message('note_on', note=int(parts[1]), velocity=int(parts[2]))
        elif parts[0] == 'cc':
            m = mido.Message('control_change', control=int(parts[1]), value=int(parts[2]))
        else:
            continue

        port.send(m)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)
