TARGET = terminal
MCU = atmega168
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c  $(BSP) $(ROOT)


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=0

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += main.c

# Library
SRC += cpu/avr/usart0__rx_buffered.c
SRC += cpu/avr/drivers/mt12864/terminal.c
SRC += cpu/avr/drivers/mt12864/bitblt.c
SRC += cpu/avr/drivers/mt12864/driver.c
SRC += util/font/Font_6x8.c

endif


include $(ROOT)/cpu/avr/Makefile
