// -----------------------------------------------------------------------------
// 1-wire bus driver implementation, the bus is directly connected.
// Parameters:
//     ONEWIRE__PORT: AVR port to which 1-wire bus is attached
//     ONEWIRE__PIN: Pin number of the AVR port
// -----------------------------------------------------------------------------

#include "onewire__bus.h"
#include "cpu/avr/gpio.h"

void onewire__bus__init(void) {
    // do nothing, after reset the pin is in input mode,
    // the bus is pulled up
}

void onewire__bus__set(const uint8_t value) {
    if (value) {
        USE_AS_INPUT(ONEWIRE);  // External pull-up pulls up line high.
    }
    else {
        USE_AS_OUTPUT(ONEWIRE);  // OUT bit is 0
    }
}


bool onewire__bus__get(void) {
    return (bool)IS_1(ONEWIRE);
}
