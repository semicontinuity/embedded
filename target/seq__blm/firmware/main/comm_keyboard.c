// =============================================================================
// This file is unused - buffered implementation was buggy (over-optimization?)
// =============================================================================

#include "comm_keyboard.h"

#include <cpu/avr/asm.h>
#include "cpu/avr/services/keyboard/keyboard.h"
#include "services/tx_ring_buffer.h"

#include "comm.h"
#include "I2CSlave.h"
#include "drivers/comm/twi_slave_callbacks.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

#include <cpu/avr/twi.h>


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


void comm_keyboard__start(void) {
    tx_ring_buffer__start();
}
