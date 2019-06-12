// =====================================================================================================================
// Communication proxy for buttons.
//
// button driver --> (button event) --> [ depressed/pressed flag + pending ]  <-- code that pumps events
// =====================================================================================================================

#include "comm_buttons.h"
#include "comm_events.h"

#include "drivers/in/encoder0__switch.h"
#include "drivers/in/encoder1__switch.h"
#include "drivers/in/encoder2__switch.h"
#include "drivers/in/encoder3__switch.h"

#include <util/bitops.h>
#include <cpu/avr/asm.h>
#include <drivers/out/led_a.h>


DEFINE_BITVAR(
    comm_buttons__button0__event_pending,
    COMM_BUTTONS__BUTTON0__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON0__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button0__event_value,
    COMM_BUTTONS__BUTTON0__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON0__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button1__event_pending,
    COMM_BUTTONS__BUTTON1__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON1__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button1__event_value,
    COMM_BUTTONS__BUTTON1__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON1__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button2__event_pending,
    COMM_BUTTONS__BUTTON2__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON2__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button2__event_value,
    COMM_BUTTONS__BUTTON2__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON2__EVENT_VALUE__BIT
);

DEFINE_BITVAR(
    comm_buttons__button3__event_pending,
    COMM_BUTTONS__BUTTON3__EVENT_PENDING__HOST, COMM_BUTTONS__BUTTON3__EVENT_PENDING__BIT
);
DEFINE_BITVAR(
    comm_buttons__button3__event_value,
    COMM_BUTTONS__BUTTON3__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON3__EVENT_VALUE__BIT
);


// buttons callbacks
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Callback to be implemented to handle encoder 0 switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder0__switch__handle_event(uint8_t new_state, uint8_t bit) {
    // copy bit
    comm_buttons__button0__event_value__set(0);
    if (new_state & (1U << bit)) {
        comm_buttons__button0__event_value__set(1);
    }
    comm_buttons__button0__event_pending__set(1);
    return true;
}

/**
 * Callback to be implemented to handle encoder 0 switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder1__switch__handle_event(uint8_t new_state, uint8_t bit) {
    // copy bit
    comm_buttons__button1__event_value__set(0);
    if (new_state & (1U << bit)) {
        comm_buttons__button1__event_value__set(1);
    }
    comm_buttons__button1__event_pending__set(1);
    return true;
}

/**
 * Callback to be implemented to handle encoder 0 switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder2__switch__handle_event(uint8_t new_state, uint8_t bit) {
    // copy bit
    comm_buttons__button2__event_value__set(0);
    if (new_state & (1U << bit)) {
        comm_buttons__button2__event_value__set(1);
    }
    comm_buttons__button2__event_pending__set(1);
    return true;
}

/**
 * Callback to be implemented to handle encoder 0 switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder3__switch__handle_event(uint8_t new_state, uint8_t bit) {
    // copy bit
    comm_buttons__button3__event_value__set(0);
    if (new_state & (1U << bit)) {
        comm_buttons__button3__event_value__set(1);
    }
    comm_buttons__button3__event_pending__set(1);
    return true;
}


// event pumping
// ---------------------------------------------------------------------------------------------------------------------

/**
 * If there are pending events, pick the event, and put it to the comm events queue
 */
void comm_buttons__run(void) {
    __asm__ __volatile__("comm_buttons__run:");
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
            return;
        }
        if (comm_buttons__button1__event_pending__get()) {
            comm_events__queue__put(
                IF_IO_BIT_SET_CONST_A_ELSE_CONST_B(
                    COMM_BUTTONS__BUTTON1__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON1__EVENT_VALUE__BIT,
                    COMM_EVENTS__BUTTONS__EVENT_DEPRESSED(1),
                    COMM_EVENTS__BUTTONS__EVENT_PRESSED(1)
                )
            );
            comm_buttons__button1__event_pending__set(0);
            return;
        }
        if (comm_buttons__button2__event_pending__get()) {
            comm_events__queue__put(
                IF_IO_BIT_SET_CONST_A_ELSE_CONST_B(
                    COMM_BUTTONS__BUTTON2__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON2__EVENT_VALUE__BIT,
                    COMM_EVENTS__BUTTONS__EVENT_DEPRESSED(2),
                    COMM_EVENTS__BUTTONS__EVENT_PRESSED(2)
                )
            );
            comm_buttons__button2__event_pending__set(0);
            return;
        }
        if (comm_buttons__button3__event_pending__get()) {
            comm_events__queue__put(
                IF_IO_BIT_SET_CONST_A_ELSE_CONST_B(
                    COMM_BUTTONS__BUTTON3__EVENT_VALUE__HOST, COMM_BUTTONS__BUTTON3__EVENT_VALUE__BIT,
                    COMM_EVENTS__BUTTONS__EVENT_DEPRESSED(3),
                    COMM_EVENTS__BUTTONS__EVENT_PRESSED(3)
                )
            );
            comm_buttons__button3__event_pending__set(0);
            return;
        }
    }
}
