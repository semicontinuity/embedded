from gcode import *

DM=3.0
RM=DM/2

OP_DY = 19

WIDTH  = 112
HEIGHT = OP_DY * 5

SIDE_W         = 20
SIDE_MOUNT_OFS = 20

NUT_DEPTH = 5.5
NUT_OFS   = 2

NW = 26
NH = 36
SCW = 7
SCH = 7 + (NH - NW)


def milling_program(g):
    return g.program(
        g.with_spindle(
            nut_opening(g, +HEIGHT/2 - NUT_OFS),
#            screw_hole(g, +HEIGHT/2 - NUT_OFS),

            nut_opening(g, -HEIGHT/2 + NUT_OFS),
#            screw_hole(g, -HEIGHT/2 + NUT_OFS),
        )
    )


def nut_opening(g, center_y):
    return (
        '',
        f'(nut opening at {center_y})',
        g.deep_round_rect_at(0, center_y, width=NW - 2*0*DM - 2*RM, height=NH - 2*0*DM - 2*RM, r=NW/2 - 2*0*RM - RM, center=True, z_to=-NUT_DEPTH),
        g.deep_round_rect_at(0, center_y, width=NW - 2*1*DM - 2*RM, height=NH - 2*1*DM - 2*RM, r=NW/2 - 2*1*RM - RM, center=True, z_to=-NUT_DEPTH),
        g.deep_round_rect_at(0, center_y, width=NW - 2*2*DM - 2*RM, height=NH - 2*2*DM - 2*RM, r=NW/2 - 2*2*RM - RM, center=True, z_to=-NUT_DEPTH),
    )


def screw_hole(g, center_y):
    return (
        f'(screw hole at {center_y})',
        g.deep_round_rect_at(0, center_y, width=SCW - 0*DM - 2*RM, height=SCH - 0*DM - 2*RM, r=7/2 - RM, center=True, z_from=-NUT_DEPTH),
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
