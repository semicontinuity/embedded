TARGET ?= $(shell basename `pwd`)
TARGET_CONF ?= $(TARGET).conf
ROOT = ../../../..
BSP = ../../bsp


CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

include $(TARGET_CONF)

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
CPPFLAGS += $(CONF)

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
CDEFS += -ffreestanding -fwhole-program -Wl,--relax
CPPFLAGS += -ffreestanding -fwhole-program -Wl,--relax

# Firmware
CPPSRC += __all__.cpp
CPPFLAGS += -I$(ROOT) -std=c++1y

include $(ROOT)/cpu/avr/Makefile
