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

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.data.properties)
include config.data.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.io_matrix__scanner.properties)
include config.io_matrix__scanner.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.io_matrix.properties)
include config.io_matrix.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.keyboard.properties)
include config.keyboard.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_events_simple.properties)
include config.comm_events_simple.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_encoder_queues.properties)
include config.comm_encoder_queues.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_buttons_queues.properties)
include config.comm_buttons_queues.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.twi_slave__handler.properties)
include config.twi_slave__handler.properties

CDEFS += -fwhole-program -Wl,--relax

ifdef BOARD_ADDRESS
CDEFS += -DTWI__SLAVE__ADDRESS=$(BOARD_ADDRESS)
endif

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile.fixed_registers.mk
include $(ROOT)/cpu/avr/Makefile
