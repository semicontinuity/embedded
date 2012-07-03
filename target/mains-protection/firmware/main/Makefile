TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(ROOT)


CDEFS += -DENABLE_VOLTAGE_MONITOR
CDEFS += -DENABLE_VOLTAGE_AVERAGING
#CDEFS += -DDEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE=inline static
SRC += __all__.c

else

CDEFS += -DINLINE=

SRC += main.c
SRC += cpu/avr/util/bcd.c
SRC += cpu/avr/drivers/display_segment_3_numeric.c
SRC += cpu/avr/drivers/display_segment_3_thread.c
SRC += $(BSP)/system_timer.c
SRC += $(BSP)/voltmeter.c
SRC += $(BSP)/buttons.c
SRC += $(BSP)/led_thread.c
SRC += $(BSP)/zero_cross_detector.c
SRC += $(BSP)/buzzer.c
#SRC += platform/mains-protection/frequency_counter.c

endif


include $(ROOT)/cpu/avr/Makefile
