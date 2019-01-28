TARGET = test
MCU = atmega328p
OPT = 2 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp/

CINCS += -I.
CINCS += -I$(BSP)
CINCS += -I$(ROOT)
CINCS += -Idrivers/sdkarte
CINCS += -Idrivers/1-wire

vpath %.c . $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

CDEFS += -DINLINE=



SRC += drivers/net/enc28j60.c

SRC += drivers/sdkarte/fat16.c
SRC += drivers/sdkarte/partition.c
SRC += drivers/sdkarte/sd.c
SRC += drivers/sdkarte/sd_raw.c
SRC += drivers/sdkarte/sdcard.c
SRC += drivers/sdkarte/spi.c

SRC += drivers/1-wire/crc8.c
SRC += drivers/1-wire/delay.c
SRC += drivers/1-wire/ds18x20.c
SRC += drivers/1-wire/onewire.c

# Firmware
SRC += main.c
SRC += services/console.c
SRC += util/hex.c
# Library
SRC += cpu/avr/util/debug.c


include $(ROOT)/cpu/avr/Makefile
