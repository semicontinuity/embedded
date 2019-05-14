// =============================================================================
// Firmware for Button LED Matrix board.
// =============================================================================

#include <cpu/avr/asm.h>
#include "cpu/avr/services/keyboard/keyboard.h"
#include "services/tx_ring_buffer.h"

#include "comm.h"
#include "I2CSlave.h"
#include "drivers/comm/twi_slave_callbacks.h"

#include "drivers/comm/ws2812b.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

#include "leds.h"

#include <util/delay.h>


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
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
        alarm__set(1);
    }
    sei();
    return true;
}

// comm callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    uint8_t value = 0;
    if (tx_ring_buffer__is_readable()) {
        value = tx_ring_buffer__get();
        alarm__set(0);
    }
    I2C_transmitByte(value);
}

void twi__slave__on_data_transmission_finished(void) {
}




// application
// -----------------------------------------------------------------------------

void application__init(void) {
    alarm__init();
    led_a__init();
    led_b__init();

    keyboard__init();

    leds__init();
    comm__init();
}


void application__start(void) {
    tx_ring_buffer__start();
    comm__start();
}


// main
// -----------------------------------------------------------------------------

int main(void) __attribute__ ((naked));
int main(void) {
    application__init();
    _delay_us(2);
    application__start();
    sei();

#if !defined(__AVR_ARCH__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif
    for(;;) {
        leds__run();
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
