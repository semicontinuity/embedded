TARGET = test
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..

CINCS += -I$(ROOT)
CINCS += -I$(ROOT)/platform/mood-lamp
vpath %.c  $(ROOT)


CDEFS += -DF_CPU=19660800UL
CDEFS += -Ddebug__putc=usart__out__write

SRC += main.c
SRC += platform/mood-lamp/pwm.c

include $(ROOT)/cpu/avr/Makefile
