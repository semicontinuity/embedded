from gcode import *

RM=2.0/2

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

#NUT_D     = 22
NUT_OFS   = 22
NUT_DEPTH = 5

def milling_program(g):
    return g.program(
        g.with_spindle(
            openings(g, -OFFSET),
            openings(g, +OFFSET),
            side_openings(g, WIDTH/2 + SIDE_MOUNT_OFS),

            nut_opening(g, +HEIGHT/2 - NUT_OFS),
            nut_opening(g, -HEIGHT/2 + NUT_OFS),

            g.deep_rect_depth_first(-WIDTH/2 - RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, HEIGHT/2 + RM, order=['W', 'S', 'E', 'N'])
        )
    )


def nut_opening(g, center_y):
    return (
        # for 22mmx32, 3 mm mill
        g.deep_round_rect_at(0, center_y, width=22 - 0*3 - 2*RM, height=32 - 0*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
        g.deep_round_rect_at(0, center_y, width=22 - 1*3 - 2*RM, height=32 - 1*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
        g.deep_round_rect_at(0, center_y, width=22 - 2*3 - 2*RM, height=32 - 2*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
        g.deep_round_rect_at(0, center_y, width=22 - 3*3 - 2*RM, height=32 - 3*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
        g.deep_round_rect_at(0, center_y, width=22 - 4*3 - 2*RM, height=32 - 4*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
        g.deep_round_rect_at(0, center_y, width=22 - 5*3 - 2*RM, height=32 - 5*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
        g.deep_round_rect_at(0, center_y, width=22 - 6*3 - 2*RM, height=32 - 6*3 - 2*RM, r=11 - RM, center=True, z_to=-5),
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
