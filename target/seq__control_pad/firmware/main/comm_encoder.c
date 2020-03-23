// =====================================================================================================================
// Implements encoder callbacks by enqueuing corresponding events in the event queue, that is read by I2C Reads
// =====================================================================================================================

#include "drivers/in/encoder0.h"
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


// encoder callbacks
// -----------------------------------------------------------------------------

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder0__handle_rotation_event(uint8_t delta) {
    led_a__toggle();
    comm_encoder__encoder0__delta += delta;
    return true;
}

/**
 * Callback to be implemented to handle encoder switch events.
 * @param new_state determines the action: 0x00 if pressed, (1 << bit) if released
 */
bool encoder0__handle_switch_event(uint8_t encoder, uint8_t new_state, uint8_t bit) {
    led_a__toggle();
    if (!comm_events__queue__is_full()) {
        comm_events__queue__put(
            IF_BIT_SET_CONST_A_ELSE_CONST_B(
                new_state, bit,
                COMM_EVENTS__ENCODER__SWITCH_EVENT_DEPRESSED(encoder),
                COMM_EVENTS__ENCODER__SWITCH_EVENT_PRESSED(encoder)
            )
        );
        return true;
    }
    return false;
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
    }
}

void comm_encoder__start(void) {
    __asm__ __volatile__("comm_encoder__start:");
    comm_encoder__encoder0__delta = 0;
}
