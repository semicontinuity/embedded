// =============================================================================
// On I2C Read request, responds with the current 1-byte event, or 0 if none
// =============================================================================

#include "comm_events.h"

#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>

#include <cpu/avr/twi.h>
#include "twi_slave_callbacks.h"

#include <drivers/out/alarm.h>
#include <drivers/out/led_b.h>


#ifdef COMM_EVENTS__EVENT__REG
register volatile uint8_t comm_events__event asm(QUOTE(COMM_EVENTS__EVENT__REG));
#else
volatile uint8_t comm_events__event;
#endif


bool comm_events__queue__is_full(void) {
    return alarm__get();
}

void comm_events__queue__put(uint8_t event) {
    comm_events__event = event;
    led_b__toggle();
    alarm__set(1);
}

// TWI Slave callbacks
// -----------------------------------------------------------------------------

void twi__slave__on_data_byte_requested(void) {
    __asm__ __volatile__("twi__slave__on_data_byte_requested:");
    twi__data__set(comm_events__event);
    twi__continue(/*false*/true, false);
    comm_events__event = 0;
    alarm__set(0);
}

void comm_events__start(void) {
    comm_events__event = 0;
}

// Temp
// ---------------------------------------------------------------------------------------------------------------------

// Handling events form encoders
// ---------------------------------------------------------------------------------------------------------------------


inline bool keyboard__handle_button_event(uint8_t button, uint8_t state, uint8_t bit) {
    return false;
}

