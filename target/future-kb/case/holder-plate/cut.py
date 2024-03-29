from gcode import *

RM=1

def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.deep_line(0, 0, 210, 0)
        )
    )


def gcode():
    gcode = GCode()
    gcode.SPINDLE_SPEED = 1000
    gcode.FEED_RATE_XY = 180
    gcode.FEED_RATE_Z = 60
    gcode.Z_UP = 3
    gcode.Z_THRESHOLD = 1
    gcode.Z_FROM = 0
    gcode.Z_DOWN = -8
    gcode.Z_STEP = 0.4
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
