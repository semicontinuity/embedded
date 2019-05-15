TARGET ?= $(shell basename `pwd`)
TARGET_CONF ?= $(TARGET).conf

ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

include $(TARGET_CONF)

# Configuration
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh)

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.io.properties)
include config.io.properties
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.leds.properties)
include config.leds.properties
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.keyboard.properties)
include config.keyboard.properties
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_leds.properties)
include config.comm_leds.properties
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_keyboard.properties)
#include config.comm_keyboard.properties
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_keyboard_simple.properties)
include config.comm_keyboard_simple.properties
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.twi_slave__handler.properties)
include config.twi_slave__handler.properties

CDEFS += -fwhole-program -Wl,--relax

ifdef BOARD_ADDRESS
CDEFS += -DTWI__SLAVE__ADDRESS=$(BOARD_ADDRESS)
endif

ifdef LEDS
CDEFS += -DLEDS__COUNT=$(LEDS)
endif

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile.fixed_registers.mk
include $(ROOT)/cpu/avr/Makefile
