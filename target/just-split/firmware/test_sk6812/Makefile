TARGET ?= $(shell basename `pwd`)
TARGET_CONF ?= $(TARGET).conf

ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

include $(TARGET_CONF)

# Configuration
CONF  = $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile.fixed_registers.mk
include $(ROOT)/cpu/avr/Makefile
