TARGET = led-dimmer
CONFIG ?= $(TARGET)
CONFIG_FILE = $(TARGET).conf

ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
include $(CONFIG_FILE)

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif


# Firmware
SRC += main.c

# BSP
SRC += pwm.c

include $(ROOT)/cpu/avr/Makefile
