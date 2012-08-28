TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


CAN_EMU_USART = 1


# Configuration
PROPS  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(PROPS)
ifeq ($(CAN_EMU_USART),1)
CDEFS += -DCAN_EMU_USART=1
CONF  = $(shell TARGET=$(TARGET)__usart sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
else
CONF  = $(shell TARGET=$(TARGET)__can sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
endif

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
SRC += comm_service.c
ifeq ($(CAN_EMU_USART),1)
SRC += usart_service.c
else
SRC += can_service.c
endif

# BSP
SRC += buttons_scanner.c
ifeq ($(CAN_EMU_USART),1)
else
SRC += can.c
endif

SRC += motor_callbacks_nop.c
SRC += motor_controller.c
SRC += motor_controller_prescaler.c
SRC += system_timer.c

# Library
ifeq ($(CAN_EMU_USART),1)
else
SRC += cpu/avr/int1.c
endif
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c


endif


include $(ROOT)/cpu/avr/Makefile
