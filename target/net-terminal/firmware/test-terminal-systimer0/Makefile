TARGET = test-terminal-systimer0
MCU = atmega16
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(BSP) $(ROOT)


# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


CDEFS += -Wl,--relax
CDEFS += --combine -fwhole-program
#CDEFS += -Wl,--section-start=.kernel=0x0001000 -Wl,--section-start=.noinit=0x008004EB  -Wl,--defsym=__stack=0x04EA
# -Wl,--defsym=__stack=0x008002f2

# Configuration
PROPS  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(PROPS)


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static" 
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c

# BSP

# Library
SRC += cpu/avr/timer0.c
SRC += cpu/avr/drivers/display/mt12864/terminal.c
SRC += cpu/avr/drivers/display/mt12864/text-output.c
SRC += cpu/avr/drivers/display/mt12864/bitblt.c
SRC += cpu/avr/drivers/display/mt12864/driver.c
SRC += util/font/Font_6x8.c

endif


include $(ROOT)/cpu/avr/Makefile
