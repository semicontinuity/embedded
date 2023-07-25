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


CDEFS += -Wl,--relax

# Configuration
PROPS  = $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh)
CDEFS += $(PROPS)

# Compile all sources in one compilation unit (because of the absent link-time optimizations)
# The goal is to have extra inlining of functions.

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -fwhole-program
CDEFS += -DINLINE="inline"
SRC += __all__.c

else

CDEFS += -DINLINE=

SRC += main.c

endif

AVRDUDE_BIN_PATH ?= $(shell dirname `which avrdude`)
AVRDUDE_ETC_PATH ?= $(shell realpath ${AVRDUDE_BIN_PATH}/../etc)
AVRDUDE_CONF_FILE ?= $(AVRDUDE_ETC_PATH)/avrdude.conf

AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = /dev/ttyUSB0
AVRDUDE_FLAGS ?= -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -C $(AVRDUDE_CONF_FILE) -b 57600

include $(ROOT)/cpu/avr/Makefile
