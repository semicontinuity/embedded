from gcode import *

RM=1

def milling_program(gcode):
    return gcode.program(
        gcode.with_spindle(
            gcode.fill_rect_x(xstart=0, ystart=-28, xstop=100, ystop=0, ystep=1)
        )
    )


def gcode():
    gcode = GCode()
    gcode.FEED_RATE_XY = 300
    gcode.FEED_RATE_Z = 60
    gcode.Z_UP = 3
    gcode.Z_THRESHOLD = 1
    gcode.Z_DOWN = -1.5
    gcode.SPINDLE_SPEED = 800
    return gcode


def main():
    for e in traverse(milling_program(gcode())):
        print(e)


if __name__ == '__main__':
    main()
