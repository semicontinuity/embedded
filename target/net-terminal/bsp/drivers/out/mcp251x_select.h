// =============================================================================
// The driver for the MCP251x Chip Select line.
// =============================================================================

#ifndef __DRIVERS__OUT__MCP251X_SELECT_H
#define __DRIVERS__OUT__MCP251X_SELECT_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/spi.h"


static inline void mcp251x_select__init(void) {
    USE_AS_OUTPUT(MCP251X_CS);
    OUT_1(MCP251X_CS);
}

static inline void mcp251x_select__on(void) {
    OUT_0(MCP251X_CS);
}

static inline void mcp251x_select__off(void) {
    OUT_1(MCP251X_CS);
}

#define mcp251x_select__run(op) do {\
    mcp251x_select__on();\
    op;\
    mcp251x_select__off();\
} while(0)


#endif