// =============================================================================
// Water leakage control module firmware
// =============================================================================


#include "cpu/avr/wdt.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/drivers/comm/modbus/modbus_rtu_driver.h"

#include <avr/interrupt.h>
#include <util/delay.h>

#include <services/uptime_counter.h>
#include <services/coils.h>
#include <services/basic_rtc.h>
#include <services/holding_registers.h>
#include <drivers/out/buzzer.h>
#include <drivers/buzzer_timer.h>

#include "drivers/in/digital_inputs.h"
#include "drivers/out/digital_outputs.h"
#include "drivers/fast_timer.h"

#include "services/slow_timer.h"
#include "services/seconds_timer.h"

#include "services/discrete_inputs.h"
//#include "services/discrete_outputs.h"

#include "valve_controller__1.h"
#include "contactor_controller.h"
#include "water_leak_sensors_controller.h"
#include "alert_controller.h"
#include "buzzer_control.h"


// =============================================================================
// Application
// =============================================================================

static void application__init(void) {
    digital_inputs__init();
    digital_outputs__init();
    buzzer__init();
    buzzer_timer__init();
    buzzer_controller__init();

    coils__init();

    holding_registers__init();

    fast_timer__init();

    modbus_rtu_driver__configure(USART0_DIVISOR(4800L));
}

static void application__start(void) {
    fast_timer__start();
    modbus_rtu_driver__start();

//    wdt__enable_unsafe(WDTO_15MS);
//    wdt_enable(WDTO_15MS);
}

static void application__stop(void) {
    fast_timer__stop();
    modbus_rtu_driver__stop();
}



// =============================================================================
// Fast timer callback (every 1ms)
// =============================================================================

void fast_timer__do_run(void) {
    discrete_inputs__run();

    water_leak_sensor_controller__run();

    if (valve_controller__1__limit_switches_state_renderer__is_runnable()) {
        valve_controller__1__limit_switches_state_renderer__run();
    }

    if (contactor_controller__is_runnable()) {
        contactor_controller__run();
    }

    contactor_controller__actual_state_renderer__run();

    alarm_controller__run();

    slow_timer__run();
//    discrete_outputs__run();

    if (holding_registers__buffer__get(HOLDING_REGISTER__ADDRESS__REBOOT) != 0) {
        //        while(1) {} // WDT enabled - will restart in 15ms (endless restart)
        _delay_ms(30);  // wait until response is sent: @4800, about 30ms
        application__stop();
        __asm__ __volatile__ ("rjmp 0\n\t");
    }
}

// =============================================================================
// Slow timer callback (every 250ms)
// =============================================================================

void slow_timer__do_run(void) {
    if (valve_controller__1__is_runnable()) {
        valve_controller__1__run();
    }

    buzzer_controller__on_slow_timer_tick();
    seconds_timer__run();
}

// =============================================================================
// Seconds timer callback (every second)
// =============================================================================

void seconds_timer__do_run(void) {
    uptime_counter__run();
    basic_rtc__run();
}

// =============================================================================
// Minutes timer callback (every minute)
// =============================================================================

void basic_rtc__on_minutes_timer_tick(void) {
    basic_rtc__run_every_minute();
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
    __asm__ __volatile__("main__loop:");
    for (;;) {
        __asm__ __volatile__("main__fast_timer:");
        if (fast_timer__is_runnable()) {
            fast_timer__run();
        }
        __asm__ __volatile__("main__modbus_rtu_driver:");
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
