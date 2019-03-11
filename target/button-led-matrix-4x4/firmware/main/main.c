// =============================================================================
// Firmware for Button LED Matrix board.
// =============================================================================

#include <cpu/avr/asm.h>
#include "comm.h"
#include "drivers/comm/twi_slave_callbacks.h"
#include "drivers/comm/ws2812b.h"
#include "services/tx_ring_buffer.h"


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
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
    }
}

// comm callbacks
// -----------------------------------------------------------------------------

uint8_t *led_ptr;
uint8_t led[16*3];

void twi__slave__on_data_byte_received(const uint8_t value) {
    *led_ptr++ = value;
}

void twi__slave__on_data_reception_finished(void) {
    ws2812_sendarray_mask((uint8_t *) led, 16*3, _BV(1));
    led_ptr = led;
}

void twi__slave__on_data_reception_aborted(void) {
    led_ptr = led;
}


// application
// -----------------------------------------------------------------------------

void application__init(void) {
    comm__init();
    led_ptr = led;
}

void application__start(void) {
    comm__start();
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
