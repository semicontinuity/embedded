TARGET = net-terminal
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



CAN_EMU = 0
CDEFS += -Wl,--relax
CDEFS += --combine -fwhole-program
#CDEFS += -Wl,--section-start=.kernel=0x0001000 -Wl,--section-start=.noinit=0x008004EB  -Wl,--defsym=__stack=0x04EA
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



# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static" -DCAN_C=\"$(CAN_C)\" -DCAN_SERVICE_C=\"$(CAN_SERVICE_C)\"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c

# BSP
SRC += alarm_client__auth.c
SRC += alarm_client__ui.c
SRC += drivers/keypad.c
SRC += system_timer.c
SRC += services/lcd_backlight_fader.c
SRC += services/lcd_backlight_service.c

# Library
SRC += cpu/avr/timer0.c
SRC += cpu/avr/drivers/display/mt12864/terminal.c
SRC += cpu/avr/drivers/display/mt12864/text-output.c
SRC += cpu/avr/drivers/display/mt12864/bitblt.c
SRC += cpu/avr/drivers/display/mt12864/driver.c
SRC += util/font/Font_6x8.c

endif


include $(ROOT)/cpu/avr/Makefile
