TARGET = test-display
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
SRC += util/font/Font_6x8.c
SRC += util/hex.c

SRC += OWIUARTBitFunctions.c
SRC += OWIHighLevelFunctions.c
SRC += common_files/OWIcrc.c

include $(ROOT)/cpu/avr/Makefile
