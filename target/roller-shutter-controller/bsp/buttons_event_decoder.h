// =============================================================================
// The event decoder for 2 buttons at pins BUTTON1 and BUTTON2.
// (The buttons must connected to the same port.)
// Decodes button events delivered at every call of buttons_event_decoder__put().
// (Called at every system tick).
// At most one event is decoded at every call,
// to allow for sequential processing of events - at most one per tick.
// This is necessary because the processing can involve long-lasting
// operations (such as network operations).
// =============================================================================

#ifndef __BUTTONS_EVENT_DECODER_H
#define __BUTTONS_EVENT_DECODER_H

#include "cpu/avr/gpio.h"
#include <stdint.h>


extern uint8_t buttons_event_decoder__pending;
extern uint8_t buttons_event_decoder__state;
extern uint8_t buttons_event_decoder__mask;


INLINE void buttons_event_decoder__out__put(uint8_t button_index, uint8_t button_state);


INLINE void buttons_event_decoder__put(uint8_t buttons_changed, uint8_t buttons_state) {
    uint8_t pending = buttons_event_decoder__pending | buttons_changed;
    uint8_t new_pending = ~buttons_event_decoder__state & pending;

    if (new_pending != pending) {
        uint8_t button_state = buttons_state & buttons_event_decoder__mask ? 0 : 1;
        buttons_event_decoder__out__put(buttons_event_decoder__state, button_state);
    }
    buttons_event_decoder__pending = new_pending;

    // Transition to the new state
    if (buttons_event_decoder__state == 0) {
        buttons_event_decoder__state = 1;
        buttons_event_decoder__mask = SIGNAL_MASK(BUTTON2);
    }
    else {
        buttons_event_decoder__state = 0;
        buttons_event_decoder__mask = SIGNAL_MASK(BUTTON1);
    }
}

#endif