// =============================================================================
// Main program.
// =============================================================================

#include <avr/interrupt.h>

#include "cpu/avr/spi.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

#include "can.h"
#include "can_selector.h"
#include "buttons.h"
#include "buttons_scanner.h"
#include "motor_controller.h"
#include "motor_controller_prescaler.h"
#include "system_timer.h"


// =============================================================================
// Controller.
// =============================================================================

void controller__run(void) {

}


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by buttons_scanner__run() when any of the buttons has changed its state.
 */
INLINE void buttons_scanner__on_change(void) {
    // It is assumed that time between pin changes (at least one system tick) is enough to send notification.
    // If for some reason it was not enough (most likely network problem), abort the transmission in progress.
    can__txb2__load(buttons_scanner__status, sizeof(buttons_scanner__status));
    can__txb2__request_to_send();
}


/**
 * Callback function, called by system_timer__run() on every system tick.
 */
INLINE void system_timer__on_system_tick(void) {
    buttons_scanner__run();
    motor_controller__prescaler__run();
}



// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    buttons__init();
    motor_controller__init();

    spi__init(SPI_CLKDIV_16);

    can_selector__init();

    mcp251x__init();

    can__init();
    can__start();

    system_timer__init();
    system_timer__start();

    sei();

    system_timer__loop();
    return 0;
}
