from gcode import *

RM=3.0/2

WIDTH  = 200
HEIGHT = 100


def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.deep_rect_depth_first(-WIDTH/2 - RM, -HEIGHT/2 - RM, WIDTH/2 + RM, HEIGHT/2 + RM, order=['W', 'S', 'E', 'N'])
        )
    )


def gcode():
    gcode = GCode()
    gcode.SPINDLE_SPEED = 1000
    gcode.FEED_RATE_XY = 120
    gcode.FEED_RATE_Z = 60
    gcode.Z_UP = 3
    gcode.Z_THRESHOLD = 1
    gcode.Z_FROM = 0
    gcode.Z_DOWN = -0.1
    gcode.Z_STEP = 0.02
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
