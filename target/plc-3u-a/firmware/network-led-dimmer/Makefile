TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

CDEFS += -DINLINE=


# Firmware
SRC += main.c
SRC += can_service.c
SRC += console_service.c
SRC += parse.c

# BSP
SRC += can.c
SRC += pwm.c

# Library
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c
SRC += cpu/avr/util/debug.c


CDEFS += -Ddebug__putc=usart__out__write


include $(ROOT)/cpu/avr/Makefile
