TARGET = can_router
MCU = atmega88
OPT = 3 -mcall-prologues
ROOT = ../../../..

CINCS += -I$(ROOT)
CINCS += -I$(ROOT)/platform/plc-6u-a
vpath %.c  $(ROOT)


# Compile all sources in one compilation util (because of the absent link-time optimizations)
WHOLE_PROGRAM=1

ifeq ($(WHOLE_PROGRAM),1)

CDEFS += -DINLINE=inline
SRC += __all__.c

else

CDEFS += -DINLINE=
SRC += usart_tx.c
SRC += can_tx.c
SRC += usart_rx.c
SRC += usart_rx_buffer.c
SRC += route.c
SRC += main.c
SRC += platform/plc-6u-a/can.c
SRC += cpu/avr/drivers/mcp251x/operations.c

endif


include $(ROOT)/cpu/avr/Makefile
