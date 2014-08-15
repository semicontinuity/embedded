TARGET = onewire-test-c++
MCU = atmega8535
OPT = 3 -Wa,-a,-ad
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
CPPSRC += main.cpp abi.cpp

include $(ROOT)/cpu/avr/Makefile
