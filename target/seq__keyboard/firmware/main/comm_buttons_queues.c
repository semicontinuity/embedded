// =====================================================================================================================
// Communication proxy for buttons.
//
// button driver --> (button event) --> [ depressed/pressed flag + pending ]  <-- code that pumps events
// =====================================================================================================================

#include "comm_buttons.h"
#include "comm_events.h"
#include "comm_buttons_queues__00_03__vars__mem.h"
#include "comm_buttons_queues__04_07__vars__mem.h"
#include "comm_buttons_queues__08_0B__vars__mem.h"
#include "comm_buttons_queues__0C_0F__vars__mem.h"
#include <util/bitops.h>
#include <cpu/avr/asm.h>
#include <avr/io.h>


#define comm_buttons__event(button) IF_IO_BIT_SET_CONST_A_ELSE_CONST_B(\
  COMM_BUTTONS__BUTTON0__EVENT_VALUE__HOST,\
  COMM_BUTTONS__BUTTON0__EVENT_VALUE__BIT,\
  COMM_EVENTS__BUTTONS__EVENT_DEPRESSED((button)),\
  COMM_EVENTS__BUTTONS__EVENT_PRESSED((button))\
)


// buttons callbacks
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Callback to be implemented to handle buttons events.
 * @param state determines the action: 0x00 if pressed, (1 << bit) if released
 */
inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    if (button == 0) {
        comm_buttons__button0__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button0__event_pending__set(1);
    }
    if (button == 1) {
        comm_buttons__button1__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button1__event_pending__set(1);
    }
    if (button == 2) {
        comm_buttons__button2__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button2__event_pending__set(1);
    }
    if (button == 3) {
        comm_buttons__button3__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button3__event_pending__set(1);
    }
    if (button == 4) {
        comm_buttons__button4__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button4__event_pending__set(1);
    }
    if (button == 5) {
        comm_buttons__button5__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button5__event_pending__set(1);
    }
    if (button == 6) {
        comm_buttons__button6__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button6__event_pending__set(1);
    }
    if (button == 7) {
        comm_buttons__button7__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button7__event_pending__set(1);
    }
    if (button == 8) {
        comm_buttons__button8__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button8__event_pending__set(1);
    }
    if (button == 9) {
        comm_buttons__button9__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button9__event_pending__set(1);
    }
    if (button == 10) {
        comm_buttons__button10__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button10__event_pending__set(1);
    }
    if (button == 11) {
        comm_buttons__button11__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button11__event_pending__set(1);
    }
    if (button == 12) {
        comm_buttons__button12__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button12__event_pending__set(1);
    }
    if (button == 13) {
        comm_buttons__button13__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button13__event_pending__set(1);
    }
    if (button == 14) {
        comm_buttons__button14__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button14__event_pending__set(1);
    }
    if (button == 15) {
        comm_buttons__button15__event_value__set_from_bit_opt(state, bit);
        comm_buttons__button15__event_pending__set(1);
    }
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
        __asm__ __volatile__("comm_buttons__run__0:");
        if (comm_buttons__button0__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(0));
            comm_buttons__button0__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__1:");
        if (comm_buttons__button1__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(1));
            comm_buttons__button1__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__2:");
        if (comm_buttons__button2__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(2));
            comm_buttons__button2__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__3:");
        if (comm_buttons__button3__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(3));
            comm_buttons__button3__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__4:");
        if (comm_buttons__button4__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(4));
            comm_buttons__button4__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__5:");
        if (comm_buttons__button5__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(5));
            comm_buttons__button5__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__6:");
        if (comm_buttons__button6__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(6));
            comm_buttons__button6__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__7:");
        if (comm_buttons__button7__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(7));
            comm_buttons__button7__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__8:");
        if (comm_buttons__button8__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(8));
            comm_buttons__button8__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__9:");
        if (comm_buttons__button9__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(9));
            comm_buttons__button9__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__10:");
        if (comm_buttons__button10__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(10));
            comm_buttons__button10__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__11:");
        if (comm_buttons__button11__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(11));
            comm_buttons__button11__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__12:");
        if (comm_buttons__button12__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(12));
            comm_buttons__button12__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__13:");
        if (comm_buttons__button13__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(13));
            comm_buttons__button13__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__14:");
        if (comm_buttons__button14__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(14));
            comm_buttons__button14__event_pending__set(0);
            return;
        }
        __asm__ __volatile__("comm_buttons__run__15:");
        if (comm_buttons__button15__event_pending__get()) {
            comm_events__queue__put(comm_buttons__event(15));
            comm_buttons__button15__event_pending__set(0);
            return;
        }
    }
}
