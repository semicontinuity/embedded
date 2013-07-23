TARGET = main
TARGET_CONF ?= $(TARGET).conf
MCU = atmega48
OPT = 2 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


include $(TARGET_CONF)

CDEFS += -Wl,--relax

CDEFS += -Wl,--section-start=.module_descriptor__value=$(MODULE_DESCRIPTOR__VALUE)
CDEFS += -Wl,--section-start=.module_descriptor__address=$(MODULE_DESCRIPTOR__ADDRESS)
CDEFS += -Wl,--section-start=.kernel=$(KERNEL__ADDRESS)
CDEFS += -Wl,--section-start=.noinit=$(NOINIT__ADDRESS)
CDEFS += -Wl,--defsym=__stack=$(STACK__ADDRESS)

# Configuration
PROPS  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(PROPS)

# Compile all sources in one compilation unit (because of the absent link-time optimizations)
# The goal is to have extra inlining of functions.
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c
SRC += kernel.c
SRC += comm_service__handler.c

# BSP
SRC += buttons_scanner.c
SRC += motor_callbacks_nop.c
SRC += motor_controller.c
SRC += motor_controller_prescaler.c

# Library
SRC += cpu/avr/timer2.c
SRC += cpu/avr/int0.c
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c
endif


include $(ROOT)/cpu/avr/Makefile
