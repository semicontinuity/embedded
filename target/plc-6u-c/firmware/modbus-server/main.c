// =============================================================================
// Sample MODBUS server.
// =============================================================================


#include "buffer.h"
#include "usart_rx.h"

#include <avr/sleep.h>
#include <stdbool.h>


int main(void) {
    buffer__init();
    delay_timer__init();

    // sleeping
    set_sleep_mode(SLEEP_MODE_IDLE);
    sleep_enable();

    usart_rx__enable();
    delay_timer__start();

    for(;;) {
        if (usart_rx__is_frame_received()) {
            // process frame
            // send response

            usart_rx__enable();
        }
        else {
            sei();
            sleep_cpu();
            cli();
        }
    }

    return 0;
}
