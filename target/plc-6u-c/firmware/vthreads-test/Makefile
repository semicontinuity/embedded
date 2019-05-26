TARGET = vthreads-test
CONFIG ?= $(TARGET)
MCU = atmega8535
OPT = 3 -Wa,-a,-ad
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(CONFIG) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
include $(CONFIG).conf

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
CDEFS += -ffreestanding -fwhole-program -Wl,--relax

# Firmware
SRC += main.c

include $(ROOT)/cpu/avr/Makefile
