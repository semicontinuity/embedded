// =============================================================================
// Roller shutter controller - main module.
// =============================================================================

#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "kernel.h"
#include "unused.h"
#include "system_timer.h"
#include "water_leak_handler.h"
#include "water_leak_sensors.h"
#include "water_leak_sensors_scanner.h"
#include "water_valve.h"

#include "comm_service__water_valve_controller.h"


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
//INLINE void water_leak_sensors_scanner__status__on_change(void) {
//    water_leak_controller__run();
//    comm_service__buttons_scanner__status__broadcast();
//}

/**
 * Called by motor_controller__run() when motor_controller__status has been changed.
 */
INLINE void water_valve_controller__value__on_change(void) {
    comm_service__water_valve_controller__value__broadcast();
}

/**
 * Called by motor_controller__run() when motor_controller__status has been changed.
 */
INLINE void motor_controller__status__on_change(void) {
//    comm_service__motor_controller__status__broadcast();
}


/**
 * Callback function, called when the motor status has been changed.
 */
void motor_controller__motor_mode__on_change(void) {
//    comm_service__motor_controller__motor_mode__broadcast();
}


/**
 * Callback function, called by system_timer__run() on every system tick.
 */
INLINE void system_timer__on_system_tick(void) {
    water_leak_sensors_scanner__run();
//    motor_controller__prescaler__run();
}


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {    
//    motor_controller__prescaler__init();
    water_leak_sensors__init();
    water_leak_sensors_scanner__init();
//    motor__init();
//    unused1__init();
//    unused2__init();
//    unused3__init();
//    system_timer__init();
    water_leak_handler__init();
}

inline static void application__start(void) {
    system_timer__start();
}

inline static void application__stop(void) {
    system_timer__stop();
}


// =============================================================================
// Entry point.
//
// Besides ordinary RESET sources, can be invoked directly by admin handler.
// In that case, the interrupts are disabled, so they need to be enabled.
// TODO: investigate brown-out behaviour (are ports re-initialized?)
// NOTE: possible optimization:
// Ext I/O registers (e.g. USART) accessed with lds/sts.
// =============================================================================
int main(void) {
    if (kernel__mode__is_set()) {
        application__stop();
    }
    else {
        kernel__init();
        kernel__start();

        application__init();
        application__start();
    }

    sei();

    for(;;);
    return 0;
}
