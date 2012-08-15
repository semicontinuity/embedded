TARGET = main
MCU = atmega48
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
################################################################################

# CPU
# Internal RC oscillator
CDEFS += -DF_CPU=8000000UL

# Buttons
# All buttons MUST be on the same port
# ==============================================================================
CDEFS += -DBUTTONS__PORT=D
CDEFS += -DBUTTON1__PORT=D
CDEFS += -DBUTTON1__PIN=7
CDEFS += -DBUTTON2__PORT=D
CDEFS += -DBUTTON2__PIN=6

# Motor control
# All motor control signals MUST be on the same port
# ==============================================================================
CDEFS += -DMOTOR__PORT=C
CDEFS += -DMOTOR_UP__PORT=C
CDEFS += -DMOTOR_UP__PIN=0
CDEFS += -DMOTOR_DOWN__PORT=C
CDEFS += -DMOTOR_DOWN__PIN=1

################################################################################

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
SRC += motor_controller.c
SRC += buttons.c

endif


include $(ROOT)/cpu/avr/Makefile
