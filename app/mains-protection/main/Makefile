TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues

CINCS += -I../../../
CINCS += -I../../../platform/mains-protection
CINCS += -I../../../platform/mains-protection/conf
CINCS += -I../../../cpu/avr
CINCS += -I../../../cpu/avr/drivers
CINCS += -I../../../cpu/avr/util
vpath %.c  ../../../platform/mains-protection ../../../cpu/avr ../../../cpu/avr/drivers ../../../cpu/avr/util


#CDEFS += -DENABLE_VOLTAGE_MONITOR
#CDEFS += -DENABLE_VOLTAGE_AVERAGING
CDEFS += -DDEBUG__MEASURE_VOLTAGE_ON_KEY_PRESS


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE=inline
SRC += __all__.c

else

CDEFS += -DINLINE=
SRC += main.c
SRC += system_timer.c
SRC += display_thread.c
SRC += numeric_display.c
#SRC += frequency_counter.c
SRC += voltmeter.c
SRC += buttons.c
SRC += bcd.c
SRC += led_thread.c
SRC += zero_cross_detector.c
SRC += buzzer.c

endif


include ../../../cpu/avr/Makefile
