from gcode import *

RM=1.7/2


ANG_SIZE_X1 = 21
ANG_SIZE_X2 = 18
ANG_SIZE_Y1 = 43
ANG_SIZE_Y2 = 26.5

OP_DY  = 19

WIDTH  = 112
HEIGHT = OP_DY * 5

SIDE_W         = 20

PW = 36
PH = 35
PDX = 21/2
PDY = 25/2

def milling_program(g):
    return g.program(
        g.with_spindle(
#            '(mount screw openings)',
#            (
#                (
#                    g.cut_cone(xy[0], xy[1], d=9.0-2*RM, to_z=-2.5, xystep=0.1, zstep=0.1),
#                    g.cylinder(xy[0], xy[1], d=4.2-2*RM, z_from=-2.5, z_to=-8, z_step=0.25)
#                )
#                for xy in [(ANG_SIZE_X1/2, HEIGHT/2 - ANG_SIZE_Y1), (-ANG_SIZE_X1/2, HEIGHT/2 - ANG_SIZE_Y1), (ANG_SIZE_X2/2, HEIGHT/2 - ANG_SIZE_Y2), (-ANG_SIZE_X2/2, HEIGHT/2 - ANG_SIZE_Y2)] for y in [-10, 10]
#            ),

#            '(plate screw openings)',
#            two_plate_holes(g),

#            '(outline)',
#            g.deep_rect_depth_first(-WIDTH/2 - RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, HEIGHT/2 + RM, order=['W', 'S', 'E', 'N']),


            # N
#            g.deep_line(-WIDTH/2 - RM, +HEIGHT/2 + RM, SIDE_W + WIDTH/2 + RM, +HEIGHT/2 + RM),
            # S
#            g.deep_line(-WIDTH/2 - RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, -HEIGHT/2 - RM),
            # E
            g.deep_line(-WIDTH/2 - RM, -HEIGHT/2 - RM, -WIDTH/2 - RM, +HEIGHT/2 + RM),
            # W
            g.deep_line(SIDE_W + WIDTH/2 + RM, -HEIGHT/2 - RM, SIDE_W + WIDTH/2 + RM, +HEIGHT/2 + RM),
        )
    )

def screw_hole(g, x, y):
    return (
        f'(screw hole at {x} {y}',
        g.cut_cone(x, y, d=9.0-2*RM, to_z=-2.5, xystep=0.1, zstep=0.1),
        g.cylinder(x, y, d=4.2-2*RM, z_from=-2.5, z_to=-8, z_step=0.25)
    )

def one_plate_holes(g, x):
    return [
        screw_hole(g, x - PDX, - PDY),
        screw_hole(g, x - PDX, + PDY),
        screw_hole(g, x + PDX, - PDY),
        screw_hole(g, x + PDX, + PDY)
    ]

def two_plate_holes(g):
    return (one_plate_holes(g, x) for x in [-WIDTH/2 + PW/2, SIDE_W + WIDTH/2 - PW/2])


def g_code():
    code = GCode()
    code.mirror_y = True
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
