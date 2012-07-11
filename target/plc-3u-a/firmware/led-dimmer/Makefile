TARGET = test
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Firmware
SRC += main.c

# BSP
SRC += pwm.c

include $(ROOT)/cpu/avr/Makefile
