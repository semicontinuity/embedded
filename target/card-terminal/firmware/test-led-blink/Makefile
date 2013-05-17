TARGET = test-led-blink
MCU = at90usb162
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


CDEFS += -Wl,--relax
CDEFS += --combine -fwhole-program
# -Wl,--defsym=__stack=0x008002f2


# Firmware
SRC += main.c

include $(ROOT)/cpu/avr/Makefile
