// =============================================================================
// one wire test 
// =============================================================================
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "onewire.h"


// main
// -----------------------------------------------------------------------------

int main(void) {

    // 1-wire
    onewire__init();
    
    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    for(;;) {
        onewire__receive_bit();
    }

    return 0;
}
