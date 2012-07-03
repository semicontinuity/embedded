TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..

CINCS += -I$(ROOT)
CINCS += -I$(ROOT)/platform/plc-3u-a/
vpath %.c $(ROOT)


SRC += main.c
SRC += platform/plc-3u-a/pwm.c

include $(ROOT)/cpu/avr/Makefile
