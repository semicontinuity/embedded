TARGET = can_router
MCU = atmega88
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp


CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE="inline static"
SRC += __all__.c

else

CDEFS += -DINLINE=

# Firmware
SRC += can_service.c
SRC += can_tx_q.c
SRC += usart_tx.c
SRC += usart_tx_q.c
SRC += can_tx.c
SRC += usart_rx.c
SRC += router.c
SRC += server.c
SRC += main.c

# BSP
SRC += can.c

# Library
SRC += cpu/avr/drivers/net/can/mcp251x/operations.c

endif


include $(ROOT)/cpu/avr/Makefile
