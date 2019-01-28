TARGET = can_router
MCU = atmega168
OPT = 3 -mcall-prologues
ROOT = ../../../..
BSP = ../../bsp


#CDEFS += -ffixed-r16 -ffixed-r17 -ffixed-r18 -ffixed-r19 -ffixed-r21 -ffixed-r26 -ffixed-r27 -ffixed-r28 -ffixed-r29 -ffixed-r30 -ffixed-r31
CDEFS += -ffixed-r16 -ffixed-r17 -ffixed-r18 -ffixed-r19 -ffixed-r21 -ffixed-r26 -ffixed-r27 -ffixed-r28 -ffixed-r29

CINCS += -I$(BSP)
CINCS += -I$(ROOT)
vpath %.c $(BSP) $(ROOT)

# Configuration
CONF  = $(shell TARGET=$(TARGET) sh $(ROOT)/parse_properties.sh)
CDEFS += $(CONF)


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
SRC += cpu/avr/spi_polled.c

endif


include $(ROOT)/cpu/avr/Makefile
