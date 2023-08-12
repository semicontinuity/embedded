// =============================================================================
// Water leakage control module firmware
// =============================================================================


#include "cpu/avr/wdt.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"

#include <avr/interrupt.h>
#include <services/uptime_counter.h>
#include <services/internal_coils.h>
#include <services/basic_rtc.h>
#include <services/holding_registers.h>

#include "drivers/in/digital_inputs.h"
#include "drivers/out/digital_outputs.h"
#include "drivers/fast_timer.h"

#include "services/slow_timer.h"
#include "services/seconds_timer.h"

#include "services/discrete_inputs.h"
#include "services/discrete_outputs.h"

#include "valve_controller__1.h"
#include "contactor_control.h"
#include "water_leak_sensors_controller.h"
#include "failure_indicator.h"
#include "buzzer_control.h"


// =============================================================================
// Fast timer callback (every ms)
// =============================================================================

void fast_timer__do_run(void) {
    wdt__reset();
    discrete_inputs__run();

    if (valve_controller__1__limit_switches_state_renderer__is_runnable()) {
        valve_controller__1__limit_switches_state_renderer__run();
    }

    if (contactor_control__is_runnable()) {
        contactor_control__run();
    }

    if (water_leak_sensor_controller__is_runnable()) {
        water_leak_sensor_controller__run();
    }

    contactor_control__actual_state_renderer__run();
    failure_indicator__run();

    buzzer_controller__on_fast_timer_tick();

    slow_timer__run();
    discrete_outputs__run();
}

// =============================================================================
// Slow timer callback (every 250ms)
// =============================================================================

void slow_timer__do_run(void) {
    if (valve_controller__1__is_runnable()) {
        valve_controller__1__run();
    }

    if (buzzer_controller__is_running()) {
        if (buzzer_controller__is_requested()) {
            buzzer_controller__run();
        } else {
            buzzer_controller__stop();
        }
    } else {
        if (buzzer_controller__is_requested()) {
            buzzer_controller__start();
        }
    }

    seconds_timer__run();
}

void seconds_timer__do_run(void) {
    uptime_counter__run();
    basic_rtc__run();
}

// =============================================================================
// Application
// =============================================================================


static void application__init(void) {
    digital_inputs__init();
    digital_outputs__init();
    discrete_outputs__init();

    internal_coils__init();
    holding_registers__init();

    fast_timer__init();

    modbus_rtu_driver__configure(USART0_DIVISOR(4800L));
}

static void application__start(void) {
    fast_timer__start();
    modbus_rtu_driver__start();

    wdt__enable_unsafe(WDTO_15MS);
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    application__start();
    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    __asm__ __volatile__( "main__loop:");
    for (;;) {
        __asm__ __volatile__( "main__modbus_rtu_driver:");
        if (fast_timer__is_runnable()) {
            fast_timer__run();
        }
        if (modbus_rtu_driver__is_runnable()) {
            modbus_rtu_driver__run();
        }
    }
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
#endif
    return 0;
#if !defined(__AVR_ARCH__)
#pragma clang diagnostic pop
#endif
}
