TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CDEFS += -ffixed-r5 -ffixed-r6


CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


# Firmware
SRC += main.c

# BSP
SRC += pwm.c

include $(ROOT)/cpu/avr/Makefile
