TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)

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
SRC += can_service.c

# BSP
SRC += buttons_scanner.c
SRC += can.c
SRC += motor.c
SRC += motor_controller.c
SRC += motor_controller_prescaler.c
SRC += system_timer.c

# Library
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c

endif


include $(ROOT)/cpu/avr/Makefile
