// =============================================================================
// Sample MODBUS server.
// =============================================================================


#include "buffer.h"
#include "delay_timer.h"
#include "modbus_server.h"
#include <avr/sleep.h>
#include <stdbool.h>


// main
// -----------------------------------------------------------------------------

int main(void) {
    buffer__init();
    delay_timer__init();

    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    modbus_server__init();

    for(;;) {
        if (!modbus_server__run()) {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}
