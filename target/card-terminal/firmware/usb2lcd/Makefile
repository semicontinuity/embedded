TARGET = usb2lcd
MCU = at90usb162
#OPT = 1 -mcall-prologues
OPT = s
ROOT = ../../../..
BSP = ../../bsp
LUFA_ROOT_PATH = $(LUFA_ROOT)/LUFA

CINCS += -I$(LUFA_ROOT)
CINCS += -I$(BSP)
CINCS += -I$(ROOT)
CINCS += -I$.

vpath %.c  $(BSP) $(ROOT) $(LUFA_ROOT_PATH)


# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
include $(TARGET).conf


#CDEFS += --combine -fwhole-program
#CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops -finline-functions

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static" 
SRC += __all__.c

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
