TARGET = one-wire-thermometer2
MCU = at90usb162
OPT = 2 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

CDEFS += -DF_CPU=16000000
#CDEFS += -Wl,--relax
#CDEFS += --combine -fwhole-program
CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops -finline-functions
# -Wl,--defsym=__stack=0x008002f2


# Firmware
SRC += main.c
SRC += cpu/avr/drivers/display/mt12232/lcd_graph_lib.c
SRC += cpu/avr/drivers/display/mt12232/terminal.c
SRC += cpu/avr/util/bcd.c
SRC += util/font/Font_6x8.c
SRC += util/hex.c

SRC += 1-wire/crc8.c 1-wire/onewire.c 1-wire/ds18x20.c
SRC += temperature.c

include $(ROOT)/cpu/avr/Makefile
