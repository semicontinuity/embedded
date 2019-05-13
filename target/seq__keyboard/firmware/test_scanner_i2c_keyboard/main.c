// =====================================================================================================================
// Test I/O matrix scanning, reading keyboard events, and transmitting them via TWI
// =====================================================================================================================
#include <cpu/avr/asm.h>

#include "data.h"

#include "drivers/io_matrix__scanner__thread__timer.h"
#include "drivers/io_matrix__in.h"
#include "drivers/io_matrix__out_rows.h"
#include "drivers/io_matrix__out_columns.h"
#include "io_matrix__scanner__thread.h"

#include "cpu/avr/services/keyboard/keyboard.h"

#include "services/tx_ring_buffer.h"

#include "drivers/out/alarm.h"
#include "drivers/out/led_a.h"
#include "drivers/out/led_b.h"

#include "I2CSlave.h"
#include "comm.h"


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
inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    cli();
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        led_a__toggle();
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
    }
    sei();
    return true;
}


// comm callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    uint8_t value = 0;
    if (tx_ring_buffer__is_readable()) {
        led_b__toggle();
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
    alarm__init();
    led_a__init();
    led_b__init();

    io_matrix__out_columns__init();
    io_matrix__out_rows__init();
    io_matrix__in__init();

    keyboard__init();
    comm__init();

    io_matrix__scanner__thread__init();
    io_matrix__scanner__thread__timer__init();
}

void application__start(void) {
    tx_ring_buffer__start();
    comm__start();
    io_matrix__scanner__thread__timer__start();
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
