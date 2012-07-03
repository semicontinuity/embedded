TARGET = test
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(ROOT)


CDEFS += -DF_CPU=19660800UL
CDEFS += -Ddebug__putc=usart__out__write

SRC += main.c
SRC += $(BSP)/pwm.c

include $(ROOT)/cpu/avr/Makefile
