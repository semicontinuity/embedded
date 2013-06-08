// =============================================================================
// The driver for the ENC28J60 Chip Select line.
// =============================================================================

#ifndef __DRIVERS__OUT__ENC28J60_SELECT_H
#define __DRIVERS__OUT__ENC28J60_SELECT_H

#include "cpu/avr/gpio.h"


static inline void enc28j60_select__init(void) {
    USE_AS_OUTPUT(ENC28J60_CS);
    OUT_1(ENC28J60_CS);
}

static inline void enc28j60_select__on(void) {
    OUT_0(ENC28J60_CS);
}

static inline void enc28j60_select__off(void) {
    OUT_1(ENC28J60_CS);
}

#endif