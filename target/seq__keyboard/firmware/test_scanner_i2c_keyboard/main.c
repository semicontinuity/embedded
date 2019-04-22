// =============================================================================
// Test scanning
// =============================================================================
#include <cpu/avr/gpio.h>

#include <cpu/avr/util/vthreads.h>
#include <cpu/avr/asm.h>
#include "drivers/scanner__thread__timer.h"

#include "cpu/avr/util/vthreads.h"

#include "drivers/out/columns.h"
#include "drivers/out/leds_rows.h"
#include "util/delay.h"

#include "data.h"

#include "services/tx_ring_buffer.h"
#include "I2CSlave.h"
#include "keyboard.h"
#include "comm.h"
#include "scanner__thread.h"


// keyboard callbacks
// -----------------------------------------------------------------------------

/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-15)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline void keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    cli();
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
    }
    sei();
}


// comm callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    uint8_t value = 0;
    if (tx_ring_buffer__is_readable()) {
        value = tx_ring_buffer__get();
    }
    I2C_transmitByte(value);
}

void twi__slave__on_data_transmission_finished(void) {
}

void twi__slave__on_data_byte_received(const uint8_t value) {
}

void twi__slave__on_data_reception_finished(void) {
}

void twi__slave__on_data_reception_aborted(void) {
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    keyboard__init();
    comm__init();
    OUT(IN__BUTTONS, 0xFF);


    led1b_row__init();
    led1g_row__init();
    led1r_row__init();

    led2b_row__init();
    led2g_row__init();
    led2r_row__init();

    column0__init();
    column1__init();
    column2__init();
    column3__init();

    scanner__thread__init();
    scanner__thread__timer__init();
}

void application__start(void) {
    tx_ring_buffer__start();
    comm__start();
    scanner__thread__timer__start();
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
    for(;;) {
        keyboard__run();
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
