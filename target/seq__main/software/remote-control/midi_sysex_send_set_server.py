#!/usr/bin/env python3
#################################################################################
# Sends command SEQ_MIDI_SYSEX_REMOTE_Mode SERVER to activate REMOTE SERVER mode.
#################################################################################
import mido
import sys


def run(port):
# remote server on
    m = mido.parse([0xf0, 0x00, 0x00,  0x7e, 0x4d, 0x00,  0x09, 0x01, 0xf7])
    port.send(m)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI OUT port name'")
    outport = mido.open_output(sys.argv[1])
    run(outport)
