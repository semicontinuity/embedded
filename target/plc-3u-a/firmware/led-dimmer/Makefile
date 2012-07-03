TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(ROOT)


SRC += main.c
SRC += $(BSP)/pwm.c

include $(ROOT)/cpu/avr/Makefile
