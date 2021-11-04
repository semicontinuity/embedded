#include "comm_keyboard.h"
#include <cpu/avr/asm.h>
#include "services/tx_ring_buffer.h"
#include "cpu/avr/services/keyboard/keyboard.h"


// keyboard tweaks
// -----------------------------------------------------------------------------


void keyboard__debounce_timer__a__expired(void) {
    keyboard__port_a__mask__reset();
}

void keyboard__debounce_timer__b__expired(void) {
    keyboard__port_b__mask__reset();
}

void keyboard__debounce_timer__c__expired(void) {
    keyboard__port_c__mask__reset();
}

void keyboard__debounce_timer__d__expired(void) {
    keyboard__port_d__mask__reset();
}


// keyboard callbacks
// -----------------------------------------------------------------------------

#define EVENT_MASK_KEY_PRESSED 0
#define EVENT_MASK_KEY_RELEASED 64


/**
 * Callback to be implemented to handle button event.
 * The type of event can be determined by checking the corresponding bit in the button's port:
 * if (state & (uint8_t)(1 << bit)) != 0, then button is released;
 * if (state & (uint8_t)(1 << bit)) == 0, then button is pressed.
 * @param button index of button (0-63)
 * @param state state of the button's port
 * @param bit index of button's pin in the port
 */
inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    // FIX_REGISTER(state); - do not use here, causes bugs
    uint8_t event = IF_BIT_SET_CONST_A_ELSE_CONST_B(
            state, bit,
            (uint8_t) (EVENT_MASK_KEY_RELEASED | button),
            (uint8_t) (EVENT_MASK_KEY_PRESSED | button));
    // Send the scan code twice, for the rare case when some kind of EMI destroys serial packet.
    // The receiving side must maintain the keyboard state, and ignore no-effect events (copies).
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        tx_ring_buffer__put(event);
    }
    if (__builtin_expect(tx_ring_buffer__is_writable(), true)) {
        tx_ring_buffer__put(event);
    }
    return true;
}
