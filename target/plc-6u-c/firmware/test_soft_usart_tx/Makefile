TARGET = test_soft_usart_tx
CONFIG ?= $(TARGET)
CONFIG_FILE = $(TARGET).conf

ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
include $(CONFIG_FILE)

CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile
