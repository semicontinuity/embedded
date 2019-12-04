// =============================================================================
// On I2C Read request, responds with the 1-byte keyboard event, or 0 if none
// =============================================================================

#include "comm_keyboard.h"

#include <avr/interrupt.h>
#include <cpu/avr/asm.h>

#include "services/tx_ring_buffer.h"

#include <cpu/avr/twi.h>
#include "twi_slave_callbacks.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>


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
    led_a__toggle();
    cli();
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        uint8_t code = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        tx_ring_buffer__put(code);
        led_b__toggle();
    }
    sei();
    return true;
}


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    __asm__ __volatile__("twi__slave__on_data_byte_requested:");
    uint8_t value = 0;
    if (tx_ring_buffer__is_readable()) {
        cli();
        value = tx_ring_buffer__get();
        sei();
    }
    twi__data__set(value);
    twi__continue(/*false*/true, false);
}


void comm_keyboard__start(void) {
    tx_ring_buffer__start();
}