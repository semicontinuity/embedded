from gcode import *

RM=0.5
D1=4.5
D2=6.5
D3=8.5

def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.deep_hexagone(0, 0, d=D1-2*RM, z_from=0, z_to=-5, z_step=0.25),
            gcode.deep_hexagone(0, 0, d=D2-2*RM, z_from=0, z_to=-5, z_step=0.25),
            gcode.deep_hexagone(0, 0, d=D3-2*RM, z_from=0, z_to=-5, z_step=0.25)
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
