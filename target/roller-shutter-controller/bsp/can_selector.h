// =============================================================================
// The driver for the CAN controller's Chip Select line.
// =============================================================================

#ifndef __CAN_SELECTOR_H
#define __CAN_SELECTOR_H

#include "cpu/avr/gpio.h"
#include "cpu/avr/spi.h"


static inline void can_selector__init(void) {
    USE_AS_OUTPUT(MCP251X_CS);
    OUT_1(MCP251X_CS);
}

static inline void can_selector__on(void) {
    OUT_0(MCP251X_CS);
}

static inline void can_selector__off(void) {
    OUT_1(MCP251X_CS);
}

#define can_selector__run(op) do {\
    can_selector__on();\
    op;\
    can_selector__off();\
} while(0)


#endif