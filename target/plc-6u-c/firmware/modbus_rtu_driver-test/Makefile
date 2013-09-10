TARGET = modbus_rtu_driver-test
#MCU = at90s2313
#MCU = at90usb162
MCU = at90s8535
#MCU = atmega8
#MCU = atmega16
OPT = 2 -Wa,-a,-ad -save-temps
OPT += -ffixed-r26 -ffixed-r27
OPT += -ffixed-r28 -ffixed-r29

#OPT += -mcall-prologues -ffixed-r30 -ffixed-r31
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile
