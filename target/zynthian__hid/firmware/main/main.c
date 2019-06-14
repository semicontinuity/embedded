// =============================================================================
// Device, that scans 4 rotary encodes with switches.
// Can be asked via I2C to report latest event (with 1-byte I2C read).
// =============================================================================

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>

#include <drivers/in/encoder0.h>
#include <drivers/in/encoder0__switch.h>
#include <cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer.h>

#include <cpu/avr/twi.h>
//#include "twi_slave__handler.h"
#include "comm_encoder.h"
#include "comm_events.h"
#include "comm_buttons.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>
#include <drivers/out/led_c.h>
#include <drivers/out/unused0.h>
#include <drivers/out/unused1.h>
#include <drivers/out/unused2.h>
#include <drivers/out/unused3.h>

#include <drivers/in/encoder0.h>
#include <drivers/in/encoder1.h>
#include <drivers/in/encoder2.h>
#include <drivers/in/encoder3.h>
#include <drivers/in/encoder0__switch.h>
#include <drivers/in/encoder1__switch.h>
#include <drivers/in/encoder2__switch.h>
#include <drivers/in/encoder3__switch.h>

#include <util/delay.h>


// Unused TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_reception_started(void) {
    __asm__ __volatile__("twi__slave__on_data_reception_started:");
    twi__continue(true, false);
}

void twi__slave__on_data_byte_received(const uint8_t value) {
    __asm__ __volatile__("twi__slave__on_data_byte_received:");
//    twi__continue(data__leds__put(value), false);
    twi__continue(/*false*/true, false);
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    encoder0__init();
    encoder0__switch__init();
    encoder1__init();
    encoder1__switch__init();
    encoder2__init();
    encoder2__switch__init();
    encoder3__init();
    encoder3__switch__init();

    alarm__init();
    led_a__init();
    led_b__init();
    led_c__init();
    unused0__init();
    unused1__init();
    unused2__init();
    unused3__init();

    twi__slave_address__set(TWI__SLAVE__ADDRESS);
}

void application__start(void) {
    encoder0__start();
    encoder1__start();
    encoder2__start();
    encoder3__start();

    comm_encoder__start();
    comm_events__start();
    twi__slave__start();
}


// main
// -----------------------------------------------------------------------------
int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
//    _delay_ms(300);
    application__start();

    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        encoder0__run();
        encoder1__run();
        encoder2__run();
        encoder3__run();
        encoder0__switch__run();
        encoder1__switch__run();
        encoder2__switch__run();
        encoder3__switch__run();

        comm_encoder__run();
        comm_buttons__run();

//        if (twi__slave__handler__is_runnable()) {
//            twi__slave__handler__run();
//        }
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
