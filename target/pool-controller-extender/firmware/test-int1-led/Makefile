TARGET = test-int1-led
TARGET_CONF ?= $(TARGET).conf
OPT = 2 -Wa,-a,-ad -finline-functions -fpredictive-commoning -fgcse-after-reload -fvect-cost-model  -fipa-cp-clone -ftree-loop-distribute-patterns -ftree-slp-vectorize
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

endif


include $(ROOT)/cpu/avr/Makefile
