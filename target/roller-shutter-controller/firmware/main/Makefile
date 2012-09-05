TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


CAN_EMU = 0
CDEFS += -Wl,--section-start=.kernel=0x00000A00 -Wl,--section-start=.kernel.data=0x00800100 -Wl,--section-start=.data=0x0080010d

# Configuration
PROPS  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(PROPS)
ifeq ($(CAN_EMU),1)
CDEFS += -DCAN_EMU=1
CONF  = $(shell TARGET=$(TARGET)__can_emu sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
CAN_C = can_emu.c
CAN_SERVICE_C = can_emu_service.c
else
CONF  = $(shell TARGET=$(TARGET)__can sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
CAN_C = can.c
CAN_SERVICE_C = can_service.c
endif

# Compile all sources in one compilation unit (because of the absent link-time optimizations)
# The goal is to have extra inlining of functions.
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static" -DCAN_C=\"$(CAN_C)\" -DCAN_SERVICE_C=\"$(CAN_SERVICE_C)\"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c
SRC += kernel.c
SRC += $(CAN_SERVICE_C)
SRC += comm_service__descriptor_memory.c
SRC += comm_service__handler.c

# BSP
SRC += buttons_scanner.c
SRC += $(CAN_C)
SRC += motor_callbacks_nop.c
SRC += motor_controller.c
SRC += motor_controller_prescaler.c
SRC += system_timer.c

# Library
ifeq ($(CAN_EMU),1)
else
SRC += cpu/avr/int1.c
endif
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c


endif


include $(ROOT)/cpu/avr/Makefile
