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
            openings(g, -OFFSET),
            openings(g, +OFFSET),
            side_openings(g, WIDTH/2 + SIDE_MOUNT_OFS)
        )
    )


def openings(g, center_x):
    return g.grid('openings', xstart=center_x - OP_DX, ystart=-2*OP_DY, xstop=center_x + OP_DX + OP_DX, ystop=2*OP_DY + OP_DY, xstep=OP_DX, ystep=OP_DY,
          element=lambda x, y: g.deep_round_rect_at(x, y, width=OP_W - 2*RM, height=OP_H - 2*RM, r=OP_R-RM, center=True)
    )

def side_openings(g, center_x):
    return g.grid('side openings', xstart=center_x, ystart=-2*OP_DY, ystop=2*OP_DY + OP_DY, ystep=OP_DY,
          element=lambda x, y: g.deep_round_rect_at(x, y, width=OP_W - 2*RM, height=OP_H - 2*RM, r=OP_R-RM, center=True)
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
