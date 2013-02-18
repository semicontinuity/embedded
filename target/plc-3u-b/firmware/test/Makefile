TARGET = test
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

CDEFS += -DINLINE=


# Firmware
SRC += main.c
SRC += console_service.c
SRC += parse.c

# Library
SRC += cpu/avr/util/debug.c


CDEFS += -Ddebug__putc=usart__out__write


include $(ROOT)/cpu/avr/Makefile
