TARGET = test
MCU = atmega48
OPT = 3 -mcall-prologues

CINCS += -I../../../
CINCS += -I../../../platform/mood-lamp
vpath %.c  ../../..


CDEFS += -DF_CPU=19660800UL
CDEFS += -Ddebug__putc=usart__out__write

SRC += main.c
SRC += platform/mood-lamp/pwm.c

include ../../../cpu/avr/Makefile
