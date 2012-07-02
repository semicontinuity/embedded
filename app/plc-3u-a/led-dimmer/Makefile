TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues

CINCS += -I../../../
CINCS += -I../../../platform/plc-3u-a/conf/
vpath %.c  ../../..


SRC += main.c
SRC += platform/plc-3u-a/pwm.c

include ../../../cpu/avr/Makefile
