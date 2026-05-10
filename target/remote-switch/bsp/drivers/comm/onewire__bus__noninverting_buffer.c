// -----------------------------------------------------------------------------
// 1-wire bus driver implementation,
// the bus is connected via non-inverting buffer.
//
// Parameters:
//     ONEWIRE__OUT__PORT, ONEWIRE__OUT__PIN:
//         AVR port and pin to which non-inverting 1-wire bus driver is attached
//     ONEWIRE__IN__PORT, ONEWIRE__IN__PIN:
//         AVR port to which 1-wire bus is attached
// -----------------------------------------------------------------------------

#include "onewire__bus.h"
#include "cpu/avr/gpio.h"


void onewire__bus__init(void) {
    USE_AS_OUTPUT(ONEWIRE__OUT);
    OUT_1(ONEWIRE__OUT);
}


void onewire__bus__set(const uint8_t value) {
    if (value) {
        OUT_1(ONEWIRE__OUT);  // Buffer pull-up pulls up the bus high.
    }
    else {
        OUT_0(ONEWIRE__OUT);  // Buffer inverts and drives the bus low.
    }
}


bool onewire__bus__get(void) {
    return (bool)IS_1(ONEWIRE__IN);
}
