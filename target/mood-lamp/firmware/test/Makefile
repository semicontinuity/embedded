TARGET ?= $(shell basename `pwd`)
TARGET_CONF ?= $(TARGET).conf
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(ROOT) $(BSP)

include $(TARGET_CONF)

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


#CDEFS += -DF_CPU=19660800UL
#CDEFS += -Ddebug__putc=usart0__out__write

SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile
