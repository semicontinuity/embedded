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
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh)

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh io.conf)
include io.conf
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh data.conf)
#include data.conf
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh io_matrix__scanner.conf)
#include io_matrix__scanner.conf
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh io_matrix.conf)
#include io_matrix.conf
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh keyboard.conf)
#include keyboard.conf
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh comm_keyboard_simple.conf)
#include comm_keyboard_simple.conf
#CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh twi_slave__handler.conf)
#include twi_slave__handler.conf

CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile
