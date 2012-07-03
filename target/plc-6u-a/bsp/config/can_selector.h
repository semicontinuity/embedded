#ifndef __CONFIG__CAN_SELECTOR_H
#define __CONFIG__CAN_SELECTOR_H


#include "cpu/avr/gpio.h"
#include "cpu/avr/spi.h"
#define MCP251X_SPI_COMM(op) do {\
    OUT_0(SLOT0_SELECT);\
    op;\
    OUT_1(SLOT0_SELECT);\
} while(0)


#endif