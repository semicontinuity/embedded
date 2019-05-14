TARGET ?= $(shell basename `pwd`)
TARGET_CONF ?= $(TARGET).conf

ROOT = ../../../..
BSP = ../../bsp

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

include $(TARGET_CONF)

ifdef FIXED_REGISTERS
OPT += $(FIXED_REGISTERS)
endif


# Configuration
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh)

CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh io.conf)
include io.conf
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh data.conf)
include data.conf
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh io_matrix__scanner.conf)
include io_matrix__scanner.conf
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh io_matrix.conf)
include io_matrix.conf
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh keyboard.conf)
include keyboard.conf
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh comm_keyboard_simple.conf)
include comm_keyboard_simple.conf
CDEFS += $(shell TARGET=$(TARGET) bash $(ROOT)/parse_properties.sh twi_slave__handler.conf)
include twi_slave__handler.conf

CDEFS += -fwhole-program -Wl,--relax

ifdef BOARD_ADDRESS
CDEFS += -DTWI__SLAVE__ADDRESS=$(BOARD_ADDRESS)
endif


ifdef FIXED_R0
OPT += -ffixed-r0
endif
ifdef FIXED_R1
OPT += -ffixed-r1
endif
ifdef FIXED_R2
OPT += -ffixed-r2
endif
ifdef FIXED_R3
OPT += -ffixed-r3
endif
ifdef FIXED_R4
OPT += -ffixed-r4
endif
ifdef FIXED_R5
OPT += -ffixed-r5
endif
ifdef FIXED_R6
OPT += -ffixed-r6
endif
ifdef FIXED_R7
OPT += -ffixed-r7
endif
ifdef FIXED_R8
OPT += -ffixed-r8
endif
ifdef FIXED_R9
OPT += -ffixed-r9
endif
ifdef FIXED_R10
OPT += -ffixed-r10
endif
ifdef FIXED_R11
OPT += -ffixed-r11
endif
ifdef FIXED_R12
OPT += -ffixed-r12
endif
ifdef FIXED_R13
OPT += -ffixed-r13
endif
ifdef FIXED_R14
OPT += -ffixed-r14
endif
ifdef FIXED_R15
OPT += -ffixed-r15
endif
ifdef FIXED_R16
OPT += -ffixed-r16
endif
ifdef FIXED_R17
OPT += -ffixed-r17
endif
ifdef FIXED_R18
OPT += -ffixed-r18
endif
ifdef FIXED_R19
OPT += -ffixed-r19
endif
ifdef FIXED_R20
OPT += -ffixed-r20
endif
ifdef FIXED_R21
OPT += -ffixed-r21
endif
ifdef FIXED_R22
OPT += -ffixed-r22
endif
ifdef FIXED_R23
OPT += -ffixed-r23
endif
ifdef FIXED_R24
OPT += -ffixed-r24
endif
ifdef FIXED_R25
OPT += -ffixed-r25
endif
ifdef FIXED_R26
OPT += -ffixed-r26
endif
ifdef FIXED_R27
OPT += -ffixed-r27
endif
ifdef FIXED_R28
OPT += -ffixed-r28
endif
ifdef FIXED_R29
OPT += -ffixed-r29
endif
ifdef FIXED_R30
OPT += -ffixed-r30
endif
ifdef FIXED_R31
OPT += -ffixed-r31
endif


# Firmware
SRC += __all__.c

include $(ROOT)/cpu/avr/Makefile
