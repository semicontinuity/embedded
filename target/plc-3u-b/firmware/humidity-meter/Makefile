TARGET = humidity-meter
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c
SRC += console_service.c
SRC += parse.c

# BSP

# Library
SRC += cpu/avr/util/debug.c
SRC += cpu/avr/util/bcd.c
SRC += cpu/avr/drivers/display/segment/static2.c

endif

include $(ROOT)/cpu/avr/Makefile
