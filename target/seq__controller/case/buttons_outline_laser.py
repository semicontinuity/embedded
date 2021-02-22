from gcode import *

RM=0.1

O_SIZE=16
O_R=2.5

POT_OP_D=8


def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.deep_rect(0 - RM, 0 - RM, 200 + RM, 150 + RM)
        )
    )


def gcode():
    gcode = GCode()
    gcode.SPINDLE_SPEED = 1000
    gcode.FEED_RATE_XY = 150
    gcode.FEED_RATE_Z = 60
    gcode.Z_UP = 3
    gcode.Z_THRESHOLD = 1
    gcode.Z_FROM = 0
    gcode.Z_DOWN = -0.04
    gcode.Z_STEP = 0.02
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
