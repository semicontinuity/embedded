// =====================================================================================================================
// Communication proxy for buttons.
//
// button driver --> (button event) --> [ depressed/pressed flag + pending ]  <-- code that pumps events
// =====================================================================================================================

#include "comm_buttons.h"

#include "drivers/in/encoder0__switch.h"
#include "comm_events.h"

#include <cpu/avr/asm.h>

#include <util/bitops.h>
#include <drivers/out/led_a.h>
#include <cpu/avr/asm.h>


DEFINE_BITVAR(
    comm_buttons__button0__event_pending,
    COMM_BUTTONS__BUTTON0__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON0__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button0__event_value,
    COMM_BUTTONS__BUTTON0__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON0__EVENT_VALUE__BIT
);


// buttons callbacks
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Callback to be implemented to handle encoder switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder0__handle_switch_event(uint8_t encoder, uint8_t new_state, uint8_t bit) {
    // copy bit
    comm_buttons__button0__event_value__set(0);
    if (new_state & (1U << bit)) {
        comm_buttons__button0__event_value__set(1);
    }
    comm_buttons__button0__event_pending__set(1);
    return true;
}


// event pumping
// ---------------------------------------------------------------------------------------------------------------------

/**
 * If there are pending events, pick the event, and put it to the comm events queue
 */
void comm_buttons__run(void) {
    if (!comm_events__queue__is_full()) {
        if (comm_buttons__button0__event_pending__get()) {
            comm_events__queue__put(
                IF_IO_BIT_SET_CONST_A_ELSE_CONST_B(
                    COMM_BUTTONS__BUTTON0__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON0__EVENT_VALUE__BIT,
                    COMM_EVENTS__BUTTONS__EVENT_DEPRESSED(0),
                    COMM_EVENTS__BUTTONS__EVENT_PRESSED(0)
                )
            );
            comm_buttons__button0__event_pending__set(0);
        }
    }
}
