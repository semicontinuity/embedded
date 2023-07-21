from gcode import *

RM=2.0/2

OP_DX  = 17.5/2
OP_DY  = 19
OP_W   = 3.1
OP_H   = 12
OP_R   = 3/2

OP_OFFSET = 43.5
OP_GAP_X  = OP_DX - 2*RM

WIDTH  = 112
HEIGHT = OP_DY * 5

SIDE_W         = 20
SIDE_MOUNT_OFS = 15

CORNER_CUT_X = -OP_OFFSET + OP_DX + OP_DX/2 - RM
CORNER_CUT_Y = -HEIGHT/2 + 3*OP_DY + RM

FRONT_X = -110

MID_X1 = FRONT_X - RM
MID_Y1 = -HEIGHT/2 + 75 + RM

MID_X2 = FRONT_X + 20 + RM
MID_Y2 = MID_Y1

MID_X3 = MID_X2
MID_Y3 = CORNER_CUT_Y

MID_X4 = CORNER_CUT_X
MID_Y4 = CORNER_CUT_Y

MID_X5 = CORNER_CUT_X
MID_Y5 = HEIGHT/2 + RM

MID_X6 = SIDE_W + WIDTH/2 + RM
MID_Y6 = HEIGHT/2 + RM


def milling_program(g):
    return g.program(
        g.with_spindle(
#            openings_w3_h3(g, -OP_OFFSET, -OP_DY),
#            openings_w2_h5(g, -OP_OFFSET + OP_DX*5/2),

#            openings_w2_h5(g, +OP_OFFSET - OP_DX*5/2),
#            openings_w3_h5(g, +OP_OFFSET),

#            side_openings(g, WIDTH/2 + SIDE_MOUNT_OFS),

            #N
#            g.deep_line(MID_X1, MID_Y1, MID_X2, MID_Y2),
            g.deep_line(MID_X2, MID_Y2, MID_X3, MID_Y3),
            g.deep_line(MID_X3, MID_Y3, MID_X4, MID_Y4),
#            g.deep_line(MID_X4, MID_Y4, MID_X5, MID_Y5),
#            g.deep_line(MID_X5, MID_Y5, MID_X6, MID_Y6),

            # S
#            g.deep_line(FRONT_X - RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, -HEIGHT/2 - RM),

            # E
#            g.deep_line(MID_X1, -HEIGHT/2 - RM, MID_X1, MID_Y1),

            # W
#            g.deep_line(SIDE_W + WIDTH/2 + RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, +HEIGHT/2 + RM),
        )
    )


def openings_w3_h3(g, center_x, center_y):
    return g.grid('openings', xstart=center_x - OP_DX, ystart=center_y - 1*OP_DY, xstop=center_x + OP_DX + OP_DX, ystop=center_y + 1*OP_DY + OP_DY, xstep=OP_DX, ystep=OP_DY,
          element=lambda x, y: g.deep_round_rect_at(x, y, width=OP_W - 2*RM, height=OP_H - 2*RM, r=OP_R-RM, center=True)
    )

def openings_w3_h5(g, center_x):
    return g.grid('openings', xstart=center_x - OP_DX, ystart=-2*OP_DY, xstop=center_x + OP_DX + OP_DX, ystop=2*OP_DY + OP_DY, xstep=OP_DX, ystep=OP_DY,
          element=lambda x, y: g.deep_round_rect_at(x, y, width=OP_W - 2*RM, height=OP_H - 2*RM, r=OP_R-RM, center=True)
    )

def openings_w2_h5(g, center_x):
    return g.grid('openings', xstart=center_x - OP_DX/2, ystart=-2*OP_DY, xstop=center_x + OP_DX/2 + OP_DX, ystop=2*OP_DY + OP_DY, xstep=OP_DX, ystep=OP_DY,
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
