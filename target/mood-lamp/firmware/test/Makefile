TARGET = test
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(ROOT) $(BSP)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


CDEFS += -DF_CPU=19660800UL
CDEFS += -Ddebug__putc=usart0__out__write

SRC += main.c
SRC += pwm.c

include $(ROOT)/cpu/avr/Makefile
