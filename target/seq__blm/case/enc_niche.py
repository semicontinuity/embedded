from gcode import *

RM=1
POT_OP_D=12


def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.cylinder(0, 0, d=12 - 2*RM, z_step=0.5),
            gcode.cylinder(0, 0, d=10 - 2*RM, z_step=0.5)
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
    gcode.Z_DOWN = -1
    gcode.Z_STEP = 0.2
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
