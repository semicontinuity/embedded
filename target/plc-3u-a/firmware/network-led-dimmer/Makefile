TARGET = network-led-dimmer
MCU = atmega8
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

CDEFS += -DINLINE=


# Firmware
SRC += main.c
SRC += can_service.c
SRC += console_service.c
SRC += parse.c

# BSP
SRC += can.c
SRC += pwm.c

# Library
SRC += cpu/avr/spi_polled.c
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c
SRC += cpu/avr/util/debug.c


include $(ROOT)/cpu/avr/Makefile
