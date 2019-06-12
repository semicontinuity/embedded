// =====================================================================================================================
// Communication proxy for encoders.
//
// encoder driver --> (rotation_event) --> [ delta ]  <-- code that fetches delta as comm event
// =====================================================================================================================

#include "comm_encoder.h"

#include "drivers/in/encoder0.h"
#include "drivers/in/encoder1.h"
#include "drivers/in/encoder2.h"
#include "drivers/in/encoder3.h"
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
 * Callback to be implemented to handle encoder rotation events of encoder 0.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder0__handle_rotation_event(uint8_t delta) {
    comm_encoder__encoder0__delta += delta;
    return true;
}

/**
 * Callback to be implemented to handle encoder rotation events of encoder 1.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder1__handle_rotation_event(uint8_t delta) {
    comm_encoder__encoder1__delta += delta;
    return true;
}

/**
 * Callback to be implemented to handle encoder rotation events of encoder 2.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder2__handle_rotation_event(uint8_t delta) {
    comm_encoder__encoder2__delta += delta;
    return true;
}

/**
 * Callback to be implemented to handle encoder rotation events of encoder 3.
 * @param delta determines the direction of rotation: 0x01 or 0xFF
 */
bool encoder3__handle_rotation_event(uint8_t delta) {
    comm_encoder__encoder3__delta += delta;
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
            return;
        }
        if (comm_encoder__encoder1__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(1, comm_encoder__encoder1__delta)
            );
            comm_encoder__encoder1__delta = 0;
            return;
        }
        if (comm_encoder__encoder2__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(2, comm_encoder__encoder2__delta)
            );
            comm_encoder__encoder2__delta = 0;
            return;
        }
        if (comm_encoder__encoder3__delta != 0) {
            comm_events__queue__put(
                COMM_EVENTS__ENCODER__ROTATION_EVENT(3, comm_encoder__encoder3__delta)
            );
            comm_encoder__encoder3__delta = 0;
            return;
        }
    }
}
