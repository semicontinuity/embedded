// =============================================================================
// Main program.
// =============================================================================

#include <avr/interrupt.h>

#include "cpu/avr/spi.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

#include "can.h"
#include "can_selector.h"
#include "buttons.h"
#include "motor_controller.h"
#include "system_timer.h"

// =============================================================================
// Button handler.
// =============================================================================

inline static void button_handler__init(void) {
    buttons__init();
}

INLINE void buttons__on_button1_changed(void) {
    motor_controller__up();
}

INLINE void buttons__on_button2_changed(void) {
    motor_controller__down();
}


// =============================================================================
// Implementation of callbacks from other modules
// =============================================================================

INLINE void on_system_tick(void) {
    buttons__run();
    motor_controller__run();
}


// =============================================================================
// Entry point
// =============================================================================

int main(void) {
    button_handler__init();
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
