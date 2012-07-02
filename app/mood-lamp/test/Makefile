TARGET = test
MCU = atmega48
OPT = 3 -mcall-prologues

CINCS += -I../../../
CINCS += -I../../../platform/mood-lamp
CINCS += -I../../../platform/mood-lamp/conf
CINCS += -I../../../cpu/avr
CINCS += -I../../../cpu/avr/drivers
CINCS += -I../../../cpu/avr/util
vpath %.c  ../../../platform/mood-lamp ../../../cpu/avr ../../../cpu/avr/drivers ../../../cpu/avr/util


CDEFS += -DF_CPU=19660800UL
SRC += main.c
SRC += pwm.c

include ../../../cpu/avr/Makefile
