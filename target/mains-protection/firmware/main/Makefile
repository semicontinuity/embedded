TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..

CINCS += -I$(ROOT)
CINCS += -I$(ROOT)/platform/mains-protection
vpath %.c  $(ROOT)


CDEFS += -DENABLE_VOLTAGE_MONITOR
CDEFS += -DENABLE_VOLTAGE_AVERAGING
#CDEFS += -DDEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE=inline
SRC += __all__.c

else

CDEFS += -DINLINE=

SRC += main.c
SRC += cpu/avr/util/bcd.c
SRC += cpu/avr/drivers/display_segment_3_numeric.c
SRC += cpu/avr/drivers/display_segment_3_thread.c
SRC += platform/mains-protection/system_timer.c
SRC += platform/mains-protection/voltmeter.c
SRC += platform/mains-protection/buttons.c
SRC += platform/mains-protection/led_thread.c
SRC += platform/mains-protection/zero_cross_detector.c
SRC += platform/mains-protection/buzzer.c
#SRC += platform/mains-protection/frequency_counter.c

endif


include $(ROOT)/cpu/avr/Makefile
