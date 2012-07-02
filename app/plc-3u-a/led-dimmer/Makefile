TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues

CINCS += -I../../../
CINCS += -I../../../platform/plc-3u-a
CINCS += -I../../../platform/plc-3u-a/conf
CINCS += -I../../../cpu/avr
CINCS += -I../../../cpu/avr/drivers
CINCS += -I../../../cpu/avr/util
vpath %.c  ../../../platform/plc-3u-a ../../../cpu/avr ../../../cpu/avr/drivers ../../../cpu/avr/util


SRC += main.c
SRC += dimmer.c

include ../../../cpu/avr/Makefile
