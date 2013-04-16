// =============================================================================
// Combo controller - main module.
// =============================================================================

#include "seconds_timer.h"
#include "system_timer.h"
#include "water_leak_sensors_scanner.h"

#include "out/amplifier_relay.h"
#include "out/siren1.h"
#include "out/siren2.h"
#include "out/water_valve.h"
#include "out/unused.h"

#include "in/water_leak_sensors.h"

#include "flags/gpio_notifications__pending.h"
#include "flags/water_leak_sensors__changed.h"
#include "flags/water_valve__changed.h"

#include "kernel.h"
#include "console_service.h"
#include "water_leak_handler.h"

#include <avr/interrupt.h>


// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

/**
 * Callback function, called by water_leak_sensors_scanner__run() when any of the sensors has changed state.
 */
INLINE void water_leak_sensors_scanner__status__on_change(void) {
    water_leak_sensors__changed__set(1);
    gpio_notifications__pending__set(1);

    water_leak_handler__run();
}


/**
 * Called on every system tick.
 */
INLINE void system_timer__out__run(void) {
    water_leak_sensors_scanner__run();
    seconds_timer__run();
}

/**
 * Called every second
 */ 
INLINE void seconds_timer__out__run(void) {
}


// =============================================================================
// Application
// =============================================================================

inline static void application__init(void) {
//    out__unused1__init();
//    out__unused2__init();
//    out__unused3__init();
    out__amplifier_relay__init();
    out__siren1__init();
    out__siren2__init();
    out__water_valve__init();

    // inputs
    in__water_leak_sensors__init();

    // flags
    gpio_notifications__pending__init();
    water_leak_sensors__changed__init();
    water_valve__changed__init();

    // services
    water_leak_sensors_scanner__init();

//    console_service__init();
    water_leak_handler__init();
    system_timer__init();
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

    // run background tasks
    for(;;) {
        cli();
        comm_service__endpoint__io__broadcast();
        sei();
    }

    return 0;
}
