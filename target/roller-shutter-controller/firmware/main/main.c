// =============================================================================
// Main program.
// =============================================================================

#include <avr/interrupt.h>

#include "cpu/avr/spi.h"

#include "can_selector.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"

#include "buttons.h"
#include "buttons_scanner.h"
#include "motor.h"
#include "motor_controller.h"
#include "motor_controller_prescaler.h"
#include "system_timer.h"
#include CAN_SERVICE_H

#include "comm_service__buttons_scanner.h"
#include "comm_service__motor_controller.h"


// =============================================================================
// Controller.
// =============================================================================

inline static void controller__run(void) {
    if (buttons_scanner__button1__is_changed()) {
        if (buttons_scanner__button1__is_released())
            motor_controller__stop();
        else
            motor_controller__move_up();
    }
    if (buttons_scanner__button2__is_changed()) {
        if (buttons_scanner__button2__is_released())
            motor_controller__stop();
        else
            motor_controller__move_down();
    }
}



// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by buttons_scanner__run() when any of the buttons has changed its state.
 */
INLINE void buttons_scanner__status__on_change(void) {
    controller__run();
    comm_service__buttons_scanner__status__broadcast();
}


/**
 * Called by motor_controller__run() when motor_controller__status has been changed.
 */
INLINE void motor_controller__status__on_change(void) {
    comm_service__motor_controller__status__broadcast();
}


/**
 * Callback function, called when the motor status has been changed.
 */
void motor_controller__motor_mode__on_change(void) {
    comm_service__motor_controller__motor_mode__broadcast();
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

    comm_service__init();
    comm_service__start();

    system_timer__init();
    system_timer__start();


    sei();
    system_timer__loop();
    return 0;
}
