TARGET = vthreads-test
MCU = atmega168
OPT = 3 -Wa,-a,-ad
OPT += -mcall-prologues -ffixed-r30 -ffixed-r31
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
CDEFS += -ffreestanding -fwhole-program -Wl,--relax

# Firmware
SRC += main.c

include $(ROOT)/cpu/avr/Makefile
