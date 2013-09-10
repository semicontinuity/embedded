// =============================================================================
// MODBUS RTU driver test.
// =============================================================================


#include "buffer.h"
#include "modbus_rtu_driver.h"
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdint.h>


bool modbus_rtu_driver__on_frame_received(void) {
    // response is echoed request
    buffer__rewind();
    return true;
}


// main
// -----------------------------------------------------------------------------

int main(void) {
    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    modbus_rtu_driver__init();

    sleep_enable();
    modbus_rtu_driver__start();

    for(;;) {
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
        }
        else {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}
