// =====================================================================================================================
// Communication proxy for encoders.
//
// encoder driver --> (rotation_event) --> [ delta ]  <-- code that fetches delta as comm event
// =====================================================================================================================

#include "comm_encoder.h"

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
// ---------------------------------------------------------------------------------------------------------------------

/**
 * Callback to be implemented to handle encoder rotation events.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder0__handle_rotation_event(uint8_t delta) {
    comm_encoder__encoder0__delta += delta;
    return true;
}

// event pumping
// ---------------------------------------------------------------------------------------------------------------------

/**
 * If there are pending events, pick the event, and put it to the comm events queue.
 */
void comm_encoder__run(void) {
    if (!comm_events__queue__is_full()) {
        if (comm_encoder__encoder0__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(0, comm_encoder__encoder0__delta)
            );
            comm_encoder__encoder0__delta = 0;
        }
    }
}
