// =============================================================================
// On I2C Read request, responds with the 1-byte keyboard event, or 0 if none
// =============================================================================

#include "comm_keyboard.h"

#include <avr/interrupt.h>
#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>

#include <cpu/avr/twi.h>
#include "twi_slave_callbacks.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_a.h>
#include <drivers/out/led_b.h>

register volatile uint8_t keyboard_event asm(QUOTE(KEYBOARD_EVENT__REG));


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
    if (!alarm__get()) {
        keyboard_event = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, (uint8_t) ('A' + button), (uint8_t) ('a' + button));
        led_b__toggle();
        alarm__set(1);
        return true;
    }
    return false;
}


// Handling events form encoders
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Callback to be implemented to handle events from encoders.
 * The type of event can be determined by checking the corresponding bit in provided state variable:
 * if (state & (uint8_t)(1 << bit)) != 0 (bit is set), then increment encoder's value;
 * if (state & (uint8_t)(1 << bit)) == 0 (bit is clear), then decrement encoder's value;
 * @param encoder index of encoder (0-3)
 */
inline void keyboard__encoders__increment_if_bit_set(uint8_t encoder, uint8_t state, uint8_t bit) {
//    uint8_t z;
//    IF_BIT_SET_INC_ELSE_DEC(z, state, bit);
}

/**
 * Callback to be implemented to handle events from encoders.
 * The type of event can be determined by checking the corresponding bit in provided state variable:
 * if (state & (uint8_t)(1 << bit)) != 0 (bit is set), then decrement encoder's value;
 * if (state & (uint8_t)(1 << bit)) == 0 (bit is clear), then increment encoder's value;
 * @param encoder index of encoder (0-3)
 */
inline void keyboard__encoders__decrement_if_bit_set(uint8_t encoder, uint8_t state, uint8_t bit) {
//    uint8_t z;
//    IF_BIT_CLEAR_INC_ELSE_DEC(z, state, bit);
}


// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    __asm__ __volatile__("twi__slave__on_data_byte_requested:");
    twi__data__set(keyboard_event);
    twi__continue(/*false*/true, false);
    keyboard_event = 0;
    alarm__set(0);
}


void comm_keyboard__start(void) {
    keyboard_event = 0;
}