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
CONF  = $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.io.properties)
include config.io.properties

CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile
