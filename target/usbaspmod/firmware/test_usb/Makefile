TARGET ?= $(shell basename `pwd`)
TARGET_CONF ?= $(TARGET).conf

#OPT += -mcall-prologues -ffixed-r30 -ffixed-r31
ROOT = ../../../..
BSP = ../../bsp

ifeq ($(VUSB_PATH),)
  $(error Define VUSB_PATH)
endif

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
CINCS += -I$(VUSB_PATH)/usbdrv
vpath %.c $(BSP) $(ROOT) $(VUSB_PATH)/usbdrv
vpath %.S $(VUSB_PATH)/usbdrv

include $(TARGET_CONF)

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
ASFLAGS += $(CONF)

#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
#CDEFS += -fwhole-program -Wl,--relax

# Firmware
SRC += __all__.c
ASRC += usbdrvasm.S

include $(ROOT)/cpu/avr/Makefile
