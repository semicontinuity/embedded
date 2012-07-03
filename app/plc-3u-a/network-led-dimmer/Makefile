TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues

CINCS += -I../../../
CINCS += -I../../../platform/plc-3u-a/conf/
vpath %.c  ../../..


SRC += main.c
SRC += console_service.c
SRC += parse.c
SRC += can_service.c

SRC += platform/plc-3u-a/can.c
SRC += platform/plc-3u-a/pwm.c
SRC += cpu/avr/drivers/mcp251x/operations.c
SRC += cpu/avr/util/debug.c


CDEFS += -Ddebug__putc=usart__out__write


include ../../../cpu/avr/Makefile
