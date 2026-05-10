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
CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile.fixed_registers.mk
include $(ROOT)/cpu/avr/Makefile

ifdef CRC16__TABLE2x256__SECTION
OBJDUMP_FLAGS = -j.text -j$(CRC16__TABLE2x256__SECTION)
endif
