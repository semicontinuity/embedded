TARGET = test-terminal-keypad
MCU = at90usb162
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(BSP) $(ROOT)


# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)
include $(TARGET).conf


CDEFS += -Wl,--relax
CDEFS += --combine -fwhole-program
#CDEFS += -Wl,--section-start=.kernel=0x0001000 -Wl,--section-start=.noinit=0x008004EB  -Wl,--defsym=__stack=0x04EA
# -Wl,--defsym=__stack=0x008002f2

# Compile all sources in one compilation unit (because of the absent link-time optimizations)
#WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static" 
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c

# BSP
SRC += drivers/keypad.c

# Library
SRC += cpu/avr/timer0.c
SRC += cpu/avr/drivers/display/mt12232/terminal.c
SRC += cpu/avr/drivers/display/mt12232/lcd_graph_lib.c
SRC += util/font/Font_6x8.c

endif


include $(ROOT)/cpu/avr/Makefile
