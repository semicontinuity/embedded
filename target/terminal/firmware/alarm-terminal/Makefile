TARGET = alarm-terminal
MCU = atmega16
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

# BSP
SRC += keyboard-scanner.c
SRC += password-processing.c
SRC += lcd-print-string-progmem.c
SRC += lcd-backlight-fading.c

# Library
SRC += cpu/avr/drivers/mt12864/terminal.c
SRC += cpu/avr/drivers/mt12864/text-output.c
SRC += cpu/avr/drivers/mt12864/bitblt.c
SRC += cpu/avr/drivers/mt12864/driver.c
SRC += util/font/Font_6x8.c

endif


include $(ROOT)/cpu/avr/Makefile
