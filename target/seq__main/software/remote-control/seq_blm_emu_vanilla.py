#!/usr/bin/env python3
import sys
import json
import time
import threading
from threading import Thread

def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)

def stdout_flush():
    sys.stdout.flush()

def stderr_print(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

def stderr_flush():
    sys.stderr.flush()


def send_bytes(b):
    stdout_print(" ".join("%02X" % i for i in b))
    stdout_flush()

def send_ping_response():
    stderr_print('PING RESPONSE')
    stderr_flush()

    send_bytes([
      0xF0,	# SYSEX start
      0x00,	# Header
      0x00,	# Header
      0x7E,	# Header
      0x4E,	# Header
      0x00,	# Device ID
      0x0F,	# ACK
      0x00,	# ACK
      0xF7	# SYSEX end
    ])


class Pinger(Thread):

   def __init__ (self):
      Thread.__init__(self)
      self._stop = threading.Event()

   def run(self):
      while not self.stopped():
        time.sleep(5)
        send_ping_response()

   def stop(self):
      self._stop.set()

   def stopped(self):
      return self._stop.isSet()



def handle_ping_request():
    send_ping_response()


def handle_info_request():
    stderr_print('INFO')
    stderr_flush()

    send_bytes([
      0xF0,	# SYSEX start
      0x00,	# Header
      0x00,	# Header
      0x7E,	# Header
      0x4E,	# Header
      0x00,	# Device ID
      0x01,	# Command 1: Layout Info
      0x10,	# Number of columns
      0x10,	# Number of rows
      0x02,	# Number of LED colors
      0x00,	# Number of extra rows
      0x00,	# Number of extra columns
      0x00,	# Number of extra buttons
      0xF7	# SYSEX end
    ])


def handle_sysex(payload):
    if payload == [0x00, 0x00, 0x7e, 0x4e, 0x00, 0x00, 0x00]:
        handle_info_request()
    elif payload == [0x00, 0x00, 0x7e, 0x4e, 0x00, 0x0F, 0x00]:
        handle_ping_request()

def handle_packed_leds_event(payload):
                channel   = payload[0] - 0xB0
                cc_number = payload[1]
                pattern = payload[2]
                if cc_number & 1:
                    pattern = pattern | 0x80
                stderr_print(payload)



def run():
    while True:
        line = sys.stdin.readline()
        if not line: break

        event = line.strip()
#        stdout_print(event, end='')

        hex_numbers = event.split(" ")
        if len(hex_numbers) > 2 and hex_numbers[0] == "F0" and hex_numbers[-1] == "F7":
            payload = [int(i, 16) for i in hex_numbers[1:-1]]
            handle_sysex(payload)
        else:
            payload = [int(i, 16) for i in hex_numbers]
            if payload[0] & 0xF0 == 0xB0:
                handle_packed_leds_event(payload)


def main():
    try:
        pinger = Pinger()
        pinger.start()
    except (KeyboardInterrupt, SystemExit):
        pinger.stop()

    run()


if __name__ == "__main__":
    main()
