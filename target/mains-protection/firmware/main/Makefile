TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


CDEFS += -DENABLE_VOLTAGE_MONITOR
CDEFS += -DENABLE_VOLTAGE_AVERAGING
#CDEFS += -DDEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS


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

# BSP
SRC += system_timer.c
SRC += voltmeter.c
SRC += buttons.c
SRC += led_thread.c
SRC += zero_cross_detector.c
SRC += buzzer.c

# Library
SRC += cpu/avr/util/bcd.c
SRC += cpu/avr/drivers/display_segment_3_numeric.c
SRC += cpu/avr/drivers/display_segment_3_thread.c

endif


include $(ROOT)/cpu/avr/Makefile
