// =============================================================================
// Simple test for display.
// =============================================================================


#include "cpu/avr/drivers/display/segment/static2.h"

#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>


int main(void) {
    display__init();
    display__render_packed(0);

    uint8_t counter = 0;
    for(;;) {
        display__render_packed(++counter);
        _delay_ms(500);
    }

    return 0;
}
