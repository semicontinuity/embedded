// =============================================================================
// MODBUS RTU driver test.
// =============================================================================


#include "buffer.h"
#include "modbus_rtu_driver.h"
#include "cpu/avr/drivers/display/segment/static2.h"

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>
#include <stdint.h>


uint16_t frames_received;
uint16_t errors;


/**
 * Invoked by the driver on every received frame
 * @return true if the response must be sent (placed to the same buffer)
 */
bool modbus_rtu_driver__on_frame_received(void) {
    display__render_packed(++frames_received);

    // response is echoed request
    buffer__rewind();
    return true;
}

void modbus_rtu_driver__on_frame_sent(void) {
}

void modbus_rtu_driver__on_protocol_error(void) {
    display__render_packed(++errors);
    display__digits__0__add_dp();
}

void modbus_rtu_driver__on_buffer_overflow(void) {
    display__render_packed(++errors);
    display__digits__0__add_dp();
}


// main
// -----------------------------------------------------------------------------

int main(void) {
    // display
    display__init();
    display__render_packed(0);

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
