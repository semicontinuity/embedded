TARGET = main
MCU = atmega16
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


CAN_EMU = 0
CDEFS += -Wl,--section-start=.kernel=0x0001000 -Wl,--section-start=.noinit=0x008004EB  -Wl,--defsym=__stack=0x04EA
# -Wl,--defsym=__stack=0x008002f2

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
# ifdef CONSOLE_SERVICE
SRC += services/console/console_service.c
SRC += services/console/parse.c
# endif

# BSP
SRC += water_leak_sensors_scanner.c
SRC += water_valve_controller.c
SRC += $(CAN_C)

# Library
SRC += cpu/avr/util/debug.c
SRC += cpu/avr/timer2.c
ifneq ($(CAN_EMU),1)
SRC += cpu/avr/int0.c
endif
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c
endif


include $(ROOT)/cpu/avr/Makefile
