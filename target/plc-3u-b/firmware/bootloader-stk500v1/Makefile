TARGET = main
MCU = atmega328p
OPT = 1 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(BSP) $(ROOT)

SRC += ATmegaBOOT_168.c
CDEFS += -DF_CPU=20000000L '-DMAX_TIME_COUNT=F_CPU>>4' '-DNUM_LED_FLASHES=1' -DBAUD_RATE=57600
CDEFS += -Wl,--section-start=.text=0x7800

include $(ROOT)/cpu/avr/Makefile
