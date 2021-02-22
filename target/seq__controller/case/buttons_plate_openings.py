from gcode import *

RM=1

O_SIZE=16
O_R=2.5

CH_SIZE=0.5
CH_STEP=0.1

POT_OP_D=8

def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.grid('chamfers', xstart=12.5, xstop=200 + 12.5, xstep=25,  ystart=12.5, ystop=150 + 12.5, ystep=25,
              element=lambda x, y: gcode.deep_round_pyramidoid_at(
                x, y, width=O_SIZE + 2*CH_SIZE - 2*RM, height=O_SIZE + 2*CH_SIZE - 2*RM, r=O_R+CH_SIZE-RM, xy_step = CH_STEP, z_step=CH_STEP, z_from=0, z_to=-CH_SIZE, center=True
              )
            ),
            gcode.grid('button openings', xstart=0 + 12.5, xstop=200 + 12.5, xstep=25,  ystart=12.5, ystop=150 + 12.5, ystep=25,
              element=lambda x, y: gcode.deep_round_rect_at(x, y, width=O_SIZE - 2*RM, height=O_SIZE - 2*RM, r=O_R-RM, center=True, z_from=-CH_SIZE)
            ),
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
