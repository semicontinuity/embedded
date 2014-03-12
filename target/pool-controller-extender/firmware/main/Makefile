TARGET = main_atmega168
TARGET_CONF ?= $(TARGET).conf
OPT = 3
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

SRC += main.c

SRC += cpu/avr/int1.c
SRC += cpu/avr/timer0.c
SRC += cpu/avr/drivers/usart0__rx.c
SRC += cpu/avr/drivers/usart0__tx.c

SRC += drivers/io/leds_tap.c
SRC += drivers/io/buttons_tap.c
SRC += drivers/io/lcd_tap.c

SRC += services/buttons_scanner.c
SRC += services/leds_scanner.c
SRC += services/tx_ring_buffer.c

endif


include $(ROOT)/cpu/avr/Makefile
