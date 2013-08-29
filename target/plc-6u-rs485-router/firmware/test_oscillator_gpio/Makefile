TARGET = test_oscillator_gpio
MCU = atxmega128a3u
OPT = 2 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops -finline-functions
CDEFS += -Wl,--relax

# Firmware
SRC += main.c

include $(ROOT)/cpu/avr/Makefile
