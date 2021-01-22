from gcode import *

RM=1

O_SIZE=16
O_R=2.5

POT_OP_D=8


def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.grid('button openings', xstart=0 + 12.5, xstop=200 + 12.5, xstep=25,  ystart=12.5, ystop=100, ystep=25,
              element=lambda x, y: gcode.deep_round_rect_at(x, y, width=O_SIZE-2*RM, height=O_SIZE-2*RM, r=O_R-RM, center=True)
            ),

            gcode.grid('potetiometer openings', xstart=225 + 12.5,  ystart=12.5, ystop=112.5, ystep=25,
              element=lambda x, y: gcode.cylinder(x, y, d=POT_OP_D - 2*RM, z_step=0.4)
            ),

            'screw openings',
            (
                (
                    gcode.cut_cone(x, y, d=6.4-2*RM, to_z=-1.7, xystep=0.1, zstep=0.1),
                    gcode.cylinder(x, y, d=3-2*RM, z_from=-1.7, z_to=-3.25, z_step=0.25)
                )
                for x in [12.5, 87.5, 112.5, 187.5, 225+12.5] for y in [25, 75]
            )
        )
    )


def gcode():
    gcode = GCode()
    gcode.SPINDLE_SPEED = 1000
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
