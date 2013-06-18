TARGET = test_can
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


# Firmware
SRC += main.c
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c
SRC += cpu/avr/spi_polled.c

include $(ROOT)/cpu/avr/Makefile
