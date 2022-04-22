from gcode import *

RM=1

O_WIDTH=104
O_HEIGHT=73
O_R=3


def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.deep_round_rect_at(0, 0, width=O_WIDTH - 2*RM, height=O_HEIGHT - 2*RM, r=O_R-RM, center=True, z_from=0)
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
    gcode.Z_DOWN = -2
    gcode.Z_STEP = 0.2
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
