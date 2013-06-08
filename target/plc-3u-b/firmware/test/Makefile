TARGET = test
MCU = atmega328p
OPT = 2 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I.
CINCS += -I$(BSP)
CINCS += -I$(ROOT)
CINCS += -Idrivers/sdkarte

vpath %.c . $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

CDEFS += -DINLINE=


# Firmware
SRC += main.c
SRC += services/console.c
SRC += util/hex.c

SRC += drivers/net/enc28j60.c
# Library
SRC += cpu/avr/util/debug.c


SRC += drivers/sdkarte/fat16.c
SRC += drivers/sdkarte/partition.c
SRC += drivers/sdkarte/sd.c
SRC += drivers/sdkarte/sd_raw.c
SRC += drivers/sdkarte/sdcard.c
SRC += drivers/sdkarte/spi.c

include $(ROOT)/cpu/avr/Makefile
