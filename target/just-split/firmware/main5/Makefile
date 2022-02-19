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

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.io_matrix__scanner.properties)
include config.io_matrix__scanner.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.io_matrix.properties)
include config.io_matrix.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.keyboard.properties)
include config.keyboard.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.gp_ring_buffer.properties)
include config.gp_ring_buffer.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.gp_buffer.properties)
include config.gp_buffer.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.twi_slave__handler.properties)
include config.twi_slave__handler.properties

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh config.comm_usart_inbound__thread.properties)
include config.comm_usart_inbound__thread.properties


CDEFS += -fwhole-program -Wl,--relax

ifdef BOARD_ADDRESS
CDEFS += -DTWI__SLAVE__ADDRESS=$(BOARD_ADDRESS)
endif

# Firmware
SRC += __all__.c


include $(ROOT)/cpu/avr/Makefile.fixed_registers.mk
include $(ROOT)/cpu/avr/Makefile
