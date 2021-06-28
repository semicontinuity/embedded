from gcode import *

RM=1

O_R=2.5

CH_SIZE=0.5
CH_STEP=0.1

POT_OP_D=8

def milling_program(gcode):
    return gcode.program(
      gcode.cut_cone(0, 0, d=7.4-2*RM, to_z=-1.7, xystep=0.1, zstep=0.1)
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
