#!/usr/bin/env python3
import mido
import sys
import os
import re
import tty
import termios
import time

STATE_LINES = 1 + 2 + 1 + 8 + 1
LCD_TOP = 1
LCD_LEFT = 0
LED_TOP = 4
LED_LEFT = 0

TERM_FD = 2
CURSOR_ROW = 0
CURSOR_COLUMN = 0

def term_write(bytes):
    os.write(TERM_FD, bytes)

def term_reset_color():
    term_write(bytes("\x1b[0m", 'utf8'))

def term_bg_color(c):
    term_write(bytes("\x1b[" + str(c) + "m", 'utf8'))

def term_color(c):
    term_write(bytes("\x1b[" + str(c) + "m", 'utf8'))


def term_next_line():
    term_write(b"\n")

def term_clear_from_cursor():
    term_write(b"\x1B[J")

def term_cursor_blink_on():
    term_write(b"\x1b[?25h")

def term_cursor_blink_off():
    term_write(b"\x1b[?25l")

def term_cursor_to(x, y):
    term_write(bytes("\x1b[" + str(x) + ";" + str(y) + "H", 'utf8'))

def term_cursor_get():
    stdin = sys.stdin.fileno()
    tattr = termios.tcgetattr(stdin)
    buf = ""

    try:
      tty.setcbreak(stdin, termios.TCSANOW)
      term_write(b"\x1b[6n")
      while True:
        buf += sys.stdin.read(1)
        if buf[-1] == "R":
            break
    finally:
      termios.tcsetattr(stdin, termios.TCSANOW, tattr)

    try:
        matches = re.match(r"^\x1b\[(\d*);(\d*)R", buf)
        groups = matches.groups()
    except AttributeError:
        return None

    return (int(groups[0]), int(groups[1]))


def handle_remote_charset(cs):
    term_cursor_to(CURSOR_ROW + LED_TOP, CURSOR_COLUMN + LED_LEFT + x)
    print("CHARSET", cs)


def handle_remote_lcd(x, y, data):
    term_cursor_to(CURSOR_ROW + LCD_TOP + y, CURSOR_COLUMN + LCD_LEFT + x)
    term_bg_color(44)
    for c in data:
        if c < 32:
            term_write(bytearray([33]))
#            term_cursor_to(CURSOR_ROW + STATE_LINES + 1, CURSOR_COLUMN)
#            term_write(bytes(str(c) + '  ', 'utf8'))
        else:
            term_write(bytearray([c]))
    term_reset_color()



def handle_remote_led(sr, nibbles):
    term_cursor_to(CURSOR_ROW + LED_TOP, CURSOR_COLUMN + LED_LEFT)
    term_color(32)

    i = 0
    while i < len(nibbles):
       l = nibbles[i]
       i += 1
       h = nibbles[i]
       i += 1

       value = (h << 4) | l

       for l in range(8):
           term_cursor_to(CURSOR_ROW + LED_TOP + l, CURSOR_COLUMN + LED_LEFT + sr*5)
           term_write(b'*' if value & 1 == 1 else b' ')
           value >>= 1

    term_reset_color()


def handle_other(m):
    term_cursor_to(CURSOR_ROW + STATE_LINES, CURSOR_COLUMN)
    term_write(bytes(str(m), 'utf8'))

def handle_debug(m):
    term_cursor_to(CURSOR_ROW + STATE_LINES + 3, CURSOR_COLUMN)
    term_write(bytearray(m))


def handle_sysex(data):
    if data[0:7] == (0x00, 0x00, 0x7e, 0x4d, 0x00, 0x09, 0x02):
        x = data[7]
        y = data[8]
        d = data[9:]
        handle_remote_lcd(x, y, d)
    elif data[0:7] == (0x00, 0x00, 0x7e, 0x4d, 0x00, 0x09, 0x04):
        handle_remote_led(data[7], data[8:])
    elif data[0:7] == (0x00, 0x00, 0x7e, 0x4d, 0x00, 0x09, 0x03):
        handle_remote_charset(data[7])
    elif data[0:6] == (0x00, 0x00, 0x7e, 0x32, 0x00, 0x0d) or data[0:6] == (0x00, 0x00, 0x7e, 0x32, 0x00, 0x0f):
        handle_debug(data[6:])
    else:
        term_cursor_to(CURSOR_ROW + STATE_LINES + 2, CURSOR_COLUMN)
        term_write(bytes(str(data), 'utf8'))


def clear_visualization_area():
    for l in range(STATE_LINES):
        term_clear_from_cursor()
        term_next_line()


def paint_visualization_area():
    term_write(bytes("\u2015", 'utf8')*80)
    term_next_line()

    term_bg_color(44)

    for l in range(2):
        term_write(bytes(" ", 'utf8')*80)
        term_next_line()

    term_reset_color()

    term_write(bytes("\u2015", 'utf8')*80)
    term_next_line()

    for l in range(8):
        term_write(bytes(" ", 'utf8')*80)
        term_next_line()

    term_write(bytes("\u2015", 'utf8')*80)
    term_next_line()



def process(port_name):
      with mido.open_input(port_name) as inport:
        for msg in inport:
            if msg.type == 'sysex':
                handle_sysex(msg.data)
            elif msg.type == 'clock':
                pass
            else:
                handle_other(msg)


def run(port_name):
    try:
      term_cursor_blink_off()
      clear_visualization_area()

      global CURSOR_ROW, CURSOR_COLUMN
      CURSOR_ROW, CURSOR_COLUMN = term_cursor_get()
      CURSOR_ROW -= STATE_LINES

      term_cursor_to(CURSOR_ROW, CURSOR_COLUMN)
      paint_visualization_area()

      process(port_name)
    except KeyboardInterrupt:
      pass
    finally:
      term_reset_color()
      term_cursor_to(CURSOR_ROW, CURSOR_COLUMN)
      clear_visualization_area()
      term_cursor_to(CURSOR_ROW, CURSOR_COLUMN)
      term_cursor_blink_on()


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit("Argument: 'MIDI IN port name'")
    run(sys.argv[1])
