TARGET = main
TARGET_CONF ?= $(TARGET).conf
MCU = at90s2313
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


include $(TARGET_CONF)


ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif


CDEFS += -Wl,--relax

# Configuration
PROPS  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(PROPS)

# Compile all sources in one compilation unit (because of the absent link-time optimizations)
# The goal is to have extra inlining of functions.

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -fwhole-program
CDEFS += -DINLINE="inline"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c
SRC += services/notifications_emitter.c
SRC += services/usart_rx.c

# BSP
SRC += drivers/buttons.c
SRC += drivers/hd44780_watcher.c

# Library
SRC += cpu/avr/int0.c
SRC += cpu/avr/drivers/usart0__rx.c
SRC += services/tx_ring_buffer.c

endif


include $(ROOT)/cpu/avr/Makefile
