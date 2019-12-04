#!/usr/bin/env python3
import sys, atexit,termios

def stdout_print(*args, **kwargs):
    print(*args, file=sys.stdout, **kwargs)


def stdout_flush():
    sys.stdout.flush()


def enable_echo(enable):
    fd = sys.stdin.fileno()
    new = termios.tcgetattr(fd)
    if enable:
        new[3] |= termios.ECHO
    else:
        new[3] &= ~termios.ECHO

    termios.tcsetattr(fd, termios.TCSANOW, new)


atexit.register(enable_echo, True)
enable_echo(False)


from pynput.keyboard import Key, Listener, Controller


class Handler(object):
  ctrl_pressed = False
  alt_pressed = False
  shift_pressed = False

  def __init__(self, sep):
    Handler.sep = sep

  @staticmethod
  def on_press(key):
    if isinstance(key, Key):
        stdout_print('press', Handler.ctrl_pressed, Handler.alt_pressed, Handler.shift_pressed, key.name, sep=Handler.sep)
        if key.name == "ctrl":
            Handler.ctrl_pressed = True
        if key.name == "alt":
            Handler.alt_pressed = True
        if key.name == "shift":
            Handler.shift_pressed = True
    else:
        stdout_print('press', Handler.ctrl_pressed, Handler.alt_pressed, Handler.shift_pressed, key.char, sep=Handler.sep)
    stdout_flush()

  @staticmethod
  def on_release(key):
    if isinstance(key, Key):
        stdout_print('release', Handler.ctrl_pressed, Handler.alt_pressed, Handler.shift_pressed, key.name, sep=Handler.sep)
        if key.name == "ctrl":
            Handler.ctrl_pressed = False
        if key.name == "alt":
            Handler.alt_pressed = False
        if key.name=="shift":
            Handler.shift_pressed = False
    else:
        stdout_print('release', Handler.ctrl_pressed, Handler.alt_pressed, Handler.shift_pressed, key.char, sep=Handler.sep)
    stdout_flush()


if __name__ == "__main__":
    handler = Handler('\t' if len(sys.argv) < 2 else sys.argv[1])
    with Listener(
        on_press=handler.on_press,
        on_release=handler.on_release) as listener:
      listener.join()

