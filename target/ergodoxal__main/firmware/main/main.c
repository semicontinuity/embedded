// =============================================================================
// Firmware for Ergodoxial keyboard
// NB: It seems that on the righ half, PD3 and PD4 inputs malfuction.
// Remapped to PB7 and PB6
// =============================================================================

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>
#include <cpu/avr/eeprom.h>

#include <cpu/avr/drivers/io_matrix/io_matrix__scanner__thread__timer.h>
#include <cpu/avr/drivers/io_matrix/io_matrix__in.h>
#include <drivers/io_matrix__out_columns.h>
#include "io_matrix__scanner__thread.h"

#include "cpu/avr/services/keyboard/keyboard.h"

#include "comm_keyboard.h"

#include <services/tracer.h>

#include "cpu/avr/usart0.h"
#include "comm_inbound.h"


// keyboard tweaks
// -----------------------------------------------------------------------------


void keyboard__debounce_timer__a__expired(void) {
    keyboard__port_a__mask__reset();
    keyboard__port_b__mask__reset();
}

void keyboard__debounce_timer__b__expired(void) {
    keyboard__port_c__mask__reset();
    keyboard__port_d__mask__reset();
}

void keyboard__debounce_timer__c__expired(void) {
    keyboard__port_e__mask__reset();
    keyboard__port_f__mask__reset();
}

void keyboard__debounce_timer__d__expired(void) {
    keyboard__port_g__mask__reset();
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    io_matrix__out_columns__init();
    io_matrix__in__init();
    PORTB |= 0xC0;  // workaround: remapped rows

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();

    keyboard__init();
    comm_inbound__init();

    usart0__init();
}

void application__start(void) {
    io_matrix__out_columns__start();
    io_matrix__in__start();

    io_matrix__scanner__thread__timer__start();

    comm_keyboard__start();
    comm_keyboard__thread__start();
    comm_inbound__thread__start();
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
    for(;;) {
        __asm__ __volatile__("main__loop__1:");
        keyboard__run();

        __asm__ __volatile__("main__loop__2:");
        while (comm_keyboard__thread__is_runnable()) {
            comm_keyboard__thread__run();
        }

        __asm__ __volatile__("main__loop__3:");
        if (comm_inbound__thread__is_runnable()) {
            comm_inbound__thread__run();
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
