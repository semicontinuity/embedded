from gcode import *

RM=1

WIDTH=200
HEIGHT=100

O_SIZE=16
O_R=2.5

O_WIDTH=3
O_HEIGHT=68
O_R=1

CH_SIZE=0.5
CH_STEP=0.1

POT_OP_D=8


def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
           gcode.grid('chamfers', xstart=12.5, xstop=WIDTH + 12.5, xstep=25,  ystart=HEIGHT/2,
              element=lambda x, y: gcode.deep_round_pyramidoid_at(
                x, y, width=O_WIDTH + 2*CH_SIZE - 2*RM, height=O_HEIGHT + 2*CH_SIZE - 2*RM, r=O_R+CH_SIZE-RM, xy_step = CH_STEP, z_step=CH_STEP, z_from=0, z_to=-CH_SIZE, center=True
              )
            ),
            gcode.grid('fader openings', xstart=0 + 12.5, xstop=WIDTH + 12.5, xstep=25,  ystart=HEIGHT/2,
              element=lambda x, y: gcode.deep_round_rect_at(x, y, width=O_WIDTH - 2*RM, height=O_HEIGHT - 2*RM, r=O_R-RM, center=True, z_from=-CH_SIZE)
            ),

            'screw openings',
            (
                (
                    gcode.cut_cone(x, y, d=6.4-2*RM, to_z=-1.7, xystep=0.1, zstep=0.1),
                    gcode.cylinder(x, y, d=3-2*RM, z_from=-1.7, z_to=-3.25, z_step=0.25)
                )
                for x in [25, 75, 125, 175] for y in [12.5, 87.5]
            )
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
