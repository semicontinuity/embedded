// =============================================================================
// Main program.
// =============================================================================

#include <avr/interrupt.h>

#include "cpu/avr/spi.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

#include "can.h"
#include "can_service.h"
#include "can_selector.h"
#include "buttons.h"
#include "buttons_scanner.h"
#include "motor.h"
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
    can_service__broadcast_buttons_status();
}



/**
 * Callback function, called by motor__up() when the motor is instructed to rotate "up".
 */
INLINE void motor__on_up(void) {
    can_service__broadcast_motor_status();
}


/**
 * Callback function, called by motor__down() when the motor is instructed to rotate "down".
 */
INLINE void motor__on_down(void) {
    can_service__broadcast_motor_status();
}


/**
 * Callback function, called by motor__stop() when the motor is instructed to stop.
 */
INLINE void motor__on_stop(void) {
    can_service__broadcast_motor_status();
}


/**
 * Called by motor_controller__run() when motor_controller__status.position has been changed.
 */
INLINE void motor_controller__status__on_change(void) {
    can_service__broadcast_motor_controller_status();
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
// TODO: investigate brown-out behaviour (are ports re-initialized?)
// =============================================================================

int main(void) {
    buttons__init();
    motor__init();

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
