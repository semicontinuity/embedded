from gcode import *

RM=1.7/2

OP_DX  = 17.5/2
OP_DY  = 19
OP_W   = 3
OP_H   = 12
OP_R   = 3/2

OFFSET = 43.5
WIDTH  = 112
HEIGHT = OP_DY * 5

SIDE_W         = 20
SIDE_MOUNT_OFS = 15


def milling_program(g):
    return g.program(
        g.with_spindle(
            g.deep_rect_depth_first(-WIDTH/2 - RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, HEIGHT/2 + RM, order=['E'])
        )
    )


def g_code():
    code = GCode()
    code.SPINDLE_SPEED = 1000
    code.FEED_RATE_XY = 120
    code.FEED_RATE_Z = 60
    code.Z_UP = 15
    code.Z_THRESHOLD = 2
    code.Z_FROM = 0
    code.Z_DOWN = -8
    code.Z_STEP = 0.4
    return code


def main():
    for e in traverse(milling_program(g_code())):
        print(e)


if __name__ == '__main__':
    main()
