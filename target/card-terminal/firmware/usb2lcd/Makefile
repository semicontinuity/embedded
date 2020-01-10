TARGET ?= $(shell basename `pwd`)
CONFIG ?= $(TARGET)
CONFIG_FILE = $(TARGET).conf
include $(CONFIG_FILE)

CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

ROOT = ../../../..
BSP = ../../bsp
LUFA_ROOT_PATH = $(LUFA_ROOT)\LUFA

LUFA_ROOT_FORWARD_SLASHES = $(subst \,/,$(LUFA_ROOT))
CINCS += -I$(LUFA_ROOT_FORWARD_SLASHES)/LUFA/Drivers/USB/Core
CINCS += -I$(LUFA_ROOT_FORWARD_SLASHES)/LUFA
CINCS += -I$(LUFA_ROOT_FORWARD_SLASHES)
CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(LUFA_ROOT_FORWARD_SLASHES)/LUFA $(BSP) $(ROOT)

#CDEFS += --combine -fwhole-program
#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops -finline-functions

ifeq ($(WHOLE_PROGRAM),1)

SRC += __all__.c
CDEFS += -fwhole-program -Wl,--relax

else

CDEFS += -DINLINE=

# Firmware
SRC += usb2lcd.c
SRC += Descriptors.c

# Library
SRC += cpu/avr/drivers/display/mt12232/terminal.c
SRC += cpu/avr/drivers/display/mt12232/lcd_graph_lib.c
SRC += util/font/Font_6x8.c

ARCH   = AVR8
SRC += Drivers/USB/Core/$(ARCH)/USBController_$(ARCH).c
SRC += Drivers/USB/Core/$(ARCH)/USBInterrupt_$(ARCH).c
SRC += Drivers/USB/Core/ConfigDescriptors.c
SRC += Drivers/USB/Core/Events.c
SRC += Drivers/USB/Core/USBTask.c

SRC += Drivers/USB/Core/$(ARCH)/Device_$(ARCH).c
SRC += Drivers/USB/Core/$(ARCH)/Endpoint_$(ARCH).c
SRC += Drivers/USB/Core/$(ARCH)/EndpointStream_$(ARCH).c
SRC += Drivers/USB/Core/DeviceStandardReq.c

SRC += Drivers/USB/Class/Device/CDCClassDevice.c

endif


include $(ROOT)/cpu/avr/Makefile
