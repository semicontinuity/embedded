TARGET = main
TARGET_CONF ?= $(TARGET).conf
MCU = atmega16
OPT = 2
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

include $(TARGET_CONF)

CAN_EMU = 0
#CDEFS += -Wl,--relax 
CDEFS += -fwhole-program
#CDEFS += --combine -fwhole-program
CDEFS += -fno-inline-functions
CDEFS += -fno-tree-loop-optimize -fno-unswitch-loops
CDEFS += -Wl,--section-start=.kernel=0x0001000 
CDEFS += -Wl,--section-start=.descriptor__address=$(DESCRIPTOR__ADDRESS)
CDEFS += -Wl,--section-start=.noinit=0x008004EB  -Wl,--defsym=__stack=0x04EA
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
SRC += descriptor.c
SRC += comm_service.c
# ifdef CONSOLE_SERVICE
#SRC += console_service.c
#SRC += parse.c
# endif
SRC += services/alarm__auth.c
SRC += services/alarm.c
SRC += services/alarm__timer.c
SRC += services/water_leak_handler__timer.c

SRC += endpoints/alarm__state.c
SRC += endpoints/siren1.c
SRC += endpoints/siren2.c

# BSP
SRC += services/seconds_timer.c
SRC += motion_sensors_scanner.c
SRC += water_leak_sensors_scanner.c
SRC += $(CAN_C)

# Library
SRC += cpu/avr/spi_polled.c
SRC += cpu/avr/util/debug.c
SRC += cpu/avr/timer2.c
ifneq ($(CAN_EMU),1)
SRC += cpu/avr/int0.c
endif
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c
endif


include $(ROOT)/cpu/avr/Makefile
