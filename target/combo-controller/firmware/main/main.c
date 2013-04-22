// =============================================================================
// Combo controller - main module.
// =============================================================================


#include "out/amplifier_relay.h"
#include "out/siren1.h"
#include "out/siren2.h"
#include "out/water_valve.h"
#include "out/unused.h"

#include "in/water_leak_sensors.h"
#include "in/motion_sensors.h"

#include "flags/gpio_notifications__pending.h"
#include "flags/water_valve__changed.h"
#include "flags/amplifier_relay__changed.h"
#include "flags/siren1__changed.h"
#include "flags/siren2__changed.h"
#include "flags/motion_sensors__changed.h"
#include "flags/water_leak_sensors__changed.h"

#include "kernel.h"

#include "alarm.h"
#include "alarm_timer.h"
#include "auth_server.h"
#include "seconds_timer.h"
#include "system_timer.h"
#include "motion_sensors_scanner.h"
#include "water_leak_sensors_scanner.h"
#include "water_leak_handler.h"

//#include "console_service.h"

#include <avr/interrupt.h>


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

void alarm__sound__on(void) {
}

void alarm__sound__off(void) {
}

void alarm__state__on_arming(void) {
}

void alarm__state__on_disarmed(void) {
}


/**
 * This procedure is called by alarm when it decided to notify about alarm condition.
 * It is called only once per session, not when alarm is switched on after it was mute.
 * Our reaction is to send SMS.
 */
void alarm__out__run(void) {    
}


/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void) {
    water_leak_sensors__changed__set(1);
    gpio_notifications__pending__set(1);

    water_leak_handler__run();
}


/**
 * Callback function, called by motion_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void motion_sensors_scanner__status__on_change(void) {
    motion_sensors__changed__set(1);
    gpio_notifications__pending__set(1);
}


/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    water_leak_sensors_scanner__run();
    motion_sensors_scanner__run();
    seconds_timer__run();
}

/**
 * Called every second.
 */ 
INLINE void seconds_timer__out__run(void) {
    alarm_timer__run();
}


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {
    out__unused1__init();
    out__unused2__init();
    out__unused3__init();
    out__amplifier_relay__init();
    out__siren1__init();
    out__siren2__init();
    out__water_valve__init();

    // inputs
    in__water_leak_sensors__init();
    in__motion_sensors__init();

    // flags
    gpio_notifications__pending__init();
    water_valve__changed__init();
    amplifier_relay__changed__init();
    siren1__changed__init();
    siren2__changed__init();
    motion_sensors__changed__init();
    water_leak_sensors__changed__init();

    // services
    alarm__init();
    auth_server__init();
    water_leak_sensors_scanner__init();
    motion_sensors_scanner__init();

    water_leak_handler__init();
    system_timer__init();

    // console_service__init();
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
//    if (kernel__mode__is_set()) {
//        application__stop();
//    }
//    else {
        kernel__init();
        kernel__start();

        application__init();
        application__start();
//    }

    sei();

    // run background tasks
    for(;;) {
        cli();
        comm_service__endpoint__io__broadcast();
        sei();
    }

//    console_service__run();
    return 0;
}
