#ifndef __CONFIG__CAN_SELECTOR_H
#define __CONFIG__CAN_SELECTOR_H


#include "cpu/avr/gpio.h"
#include "cpu/avr/spi.h"
#define MCP251X_SPI_COMM(op) do {\
    OUT_0(SS);\
    op;\
    OUT_1(SS);\
} while(0)


#endif