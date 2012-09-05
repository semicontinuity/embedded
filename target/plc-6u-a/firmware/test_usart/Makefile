TARGET = test_usart
MCU = atmega168
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp


CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=0

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += usart_rx.c
SRC += main.c


endif


include $(ROOT)/cpu/avr/Makefile
