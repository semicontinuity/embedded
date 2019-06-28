// =====================================================================================================================
// Communication proxy for encoders.
//
// encoder driver --> (rotation_event) --> [ delta ]  <-- code that fetches delta as comm event
// =====================================================================================================================

#include "comm_encoder.h"
#include "comm_events.h"

#include <avr/interrupt.h>
#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>

#include <drivers/out/led_a.h>                  


#ifdef COMM_ENCODER__ENCODER0__DELTA__REG
register volatile uint8_t comm_encoder__encoder0__delta asm(QUOTE(COMM_ENCODER__ENCODER0__DELTA__REG));
#else
volatile uint8_t comm_encoder__encoder0__delta;
#endif

#ifdef COMM_ENCODER__ENCODER1__DELTA__REG
register volatile uint8_t comm_encoder__encoder1__delta asm(QUOTE(COMM_ENCODER__ENCODER1__DELTA__REG));
#else
volatile uint8_t comm_encoder__encoder1__delta;
#endif

#ifdef COMM_ENCODER__ENCODER2__DELTA__REG
register volatile uint8_t comm_encoder__encoder2__delta asm(QUOTE(COMM_ENCODER__ENCODER2__DELTA__REG));
#else
volatile uint8_t comm_encoder__encoder2__delta;
#endif

#ifdef COMM_ENCODER__ENCODER3__DELTA__REG
register volatile uint8_t comm_encoder__encoder3__delta asm(QUOTE(COMM_ENCODER__ENCODER3__DELTA__REG));
#else
volatile uint8_t comm_encoder__encoder3__delta;
#endif


// encoder callbacks
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Callback to be implemented to handle events from encoders.
 * The type of event can be determined by checking the corresponding bit in provided state variable:
 * if (state & (uint8_t)(1 << bit)) != 0 (bit is set), then increment encoder's value;
 * if (state & (uint8_t)(1 << bit)) == 0 (bit is clear), then decrement encoder's value;
 * @param encoder index of encoder (0-3)
 */
void keyboard__encoders__increment_if_bit_set(const uint8_t encoder, const uint8_t state, const uint8_t bit) {
/*
    if (encoder == 0) {
        if (!(state & (1U << bit))) DEC(comm_encoder__encoder0__delta);
        if (state & (1U << bit)) INC(comm_encoder__encoder0__delta);
//        IF_BIT_SET_INC_ELSE_DEC(comm_encoder__encoder0__delta, state, bit);
    } else if (encoder == 1) {
        if (state & (1U << bit)) INC(comm_encoder__encoder1__delta);
        if (!(state & (1U << bit))) DEC(comm_encoder__encoder1__delta);
//        IF_BIT_SET_INC_ELSE_DEC(comm_encoder__encoder1__delta, state, bit);
    } else if (encoder == 2) {
        if (state & (1U << bit)) INC(comm_encoder__encoder2__delta);
        if (!(state & (1U << bit))) DEC(comm_encoder__encoder2__delta);
//        IF_BIT_SET_INC_ELSE_DEC(comm_encoder__encoder2__delta, state, bit);
    } else if (encoder == 3) {
        if (state & (1U << bit)) INC(comm_encoder__encoder3__delta);
        if (!(state & (1U << bit))) DEC(comm_encoder__encoder3__delta);
//        IF_BIT_SET_INC_ELSE_DEC(comm_encoder__encoder3__delta, state, bit);
    }
*/

/*
    uint8_t delta = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, 1, 0xFF);
    if (encoder == 0) {
        comm_encoder__encoder0__delta += delta;
    } else if (encoder == 1) {
        comm_encoder__encoder1__delta += delta;
    } else if (encoder == 2) {
        comm_encoder__encoder2__delta += delta;
    } else if (encoder == 3) {
        comm_encoder__encoder3__delta += delta;
    }
*/

    if (encoder == 0) {
        IF_BIT_SET_INC(comm_encoder__encoder0__delta, state, bit);
        IF_BIT_CLEAR_DEC(comm_encoder__encoder0__delta, state, bit);
    } else if (encoder == 1) {
        IF_BIT_SET_INC(comm_encoder__encoder1__delta, state, bit);
        IF_BIT_CLEAR_DEC(comm_encoder__encoder1__delta, state, bit);
    } else if (encoder == 2) {
        IF_BIT_SET_INC(comm_encoder__encoder2__delta, state, bit);
        IF_BIT_CLEAR_DEC(comm_encoder__encoder2__delta, state, bit);
    } else if (encoder == 3) {
        IF_BIT_SET_INC(comm_encoder__encoder3__delta, state, bit);
        IF_BIT_CLEAR_DEC(comm_encoder__encoder3__delta, state, bit);
    }
}

/**
 * Callback to be implemented to handle events from encoders.
 * The type of event can be determined by checking the corresponding bit in provided state variable:
 * if (state & (uint8_t)(1 << bit)) != 0 (bit is set), then decrement encoder's value;
 * if (state & (uint8_t)(1 << bit)) == 0 (bit is clear), then increment encoder's value;
 * @param encoder index of encoder (0-3)
 */
void keyboard__encoders__decrement_if_bit_set(const uint8_t encoder, const uint8_t state, const uint8_t bit) {
/*
    if (encoder == 0) {
//        IF_BIT_CLEAR_INC_ELSE_DEC(comm_encoder__encoder0__delta, state, bit);
        if (state & (1U << bit)) DEC(comm_encoder__encoder0__delta);
        if (!(state & (1U << bit))) INC(comm_encoder__encoder0__delta);
    } else if (encoder == 1) {
//        IF_BIT_CLEAR_INC_ELSE_DEC(comm_encoder__encoder1__delta, state, bit);
        if (state & (1U << bit)) DEC(comm_encoder__encoder1__delta);
        if (!(state & (1U << bit))) INC(comm_encoder__encoder1__delta);
    } else if (encoder == 2) {
//        IF_BIT_CLEAR_INC_ELSE_DEC(comm_encoder__encoder2__delta, state, bit);
        if (state & (1U << bit)) DEC(comm_encoder__encoder2__delta);
        if (!(state & (1U << bit))) INC(comm_encoder__encoder2__delta);
    } else if (encoder == 3) {
//        IF_BIT_CLEAR_INC_ELSE_DEC(comm_encoder__encoder3__delta, state, bit);
        if (state & (1U << bit)) DEC(comm_encoder__encoder3__delta);
        if (!(state & (1U << bit))) INC(comm_encoder__encoder3__delta);
    }
*/
/*
    uint8_t delta = IF_BIT_SET_CONST_A_ELSE_CONST_B(state, bit, 0xFF, 1);
    if (encoder == 0) {
        comm_encoder__encoder0__delta += delta;
    } else if (encoder == 1) {
        comm_encoder__encoder1__delta += delta;
    } else if (encoder == 2) {
        comm_encoder__encoder2__delta += delta;
    } else if (encoder == 3) {
        comm_encoder__encoder3__delta += delta;
    }
*/
    if (encoder == 0) {
        IF_BIT_SET_DEC(comm_encoder__encoder0__delta, state, bit);
        IF_BIT_CLEAR_INC(comm_encoder__encoder0__delta, state, bit);
    } else if (encoder == 1) {
        IF_BIT_SET_DEC(comm_encoder__encoder1__delta, state, bit);
        IF_BIT_CLEAR_INC(comm_encoder__encoder1__delta, state, bit);
    } else if (encoder == 2) {
        IF_BIT_SET_DEC(comm_encoder__encoder2__delta, state, bit);
        IF_BIT_CLEAR_INC(comm_encoder__encoder2__delta, state, bit);
    } else if (encoder == 3) {
        IF_BIT_SET_DEC(comm_encoder__encoder3__delta, state, bit);
        IF_BIT_CLEAR_INC(comm_encoder__encoder3__delta, state, bit);
    }
}


// event pumping
// ---------------------------------------------------------------------------------------------------------------------

/**
 * If there are pending events, pick the event, and put it to the comm events queue.
 */
void comm_encoder__run(void) {
    __asm__ __volatile__("comm_encoder__run:");
    if (!comm_events__queue__is_full()) {
        __asm__ __volatile__("comm_encoder__run__0:");
        if (comm_encoder__encoder0__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(0, comm_encoder__encoder0__delta)
            );
            comm_encoder__encoder0__delta = 0;
            return;
        }
        __asm__ __volatile__("comm_encoder__run__1:");
        if (comm_encoder__encoder1__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(1, comm_encoder__encoder1__delta)
            );
            comm_encoder__encoder1__delta = 0;
            return;
        }
        __asm__ __volatile__("comm_encoder__run__2:");
        if (comm_encoder__encoder2__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(2, comm_encoder__encoder2__delta)
            );
            comm_encoder__encoder2__delta = 0;
            return;
        }
        __asm__ __volatile__("comm_encoder__run__3:");
        if (comm_encoder__encoder3__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(3, comm_encoder__encoder3__delta)
            );
            comm_encoder__encoder3__delta = 0;
            return;
        }
    }
}

void comm_encoder__start(void) {
    __asm__ __volatile__("comm_encoder__start:");
    comm_encoder__encoder0__delta = 0;
    comm_encoder__encoder1__delta = 0;
    comm_encoder__encoder2__delta = 0;
    comm_encoder__encoder3__delta = 0;
}