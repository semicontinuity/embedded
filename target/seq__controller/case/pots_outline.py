from gcode import *

RM=1

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
    gcode.SPINDLE_SPEED = 300
    gcode.FEED_RATE_XY = 720
    gcode.FEED_RATE_Z = 60
    gcode.Z_UP = 3
    gcode.Z_THRESHOLD = 1
    gcode.Z_FROM = 0
    gcode.Z_DOWN = -3.4
    gcode.Z_STEP = 0.2
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
