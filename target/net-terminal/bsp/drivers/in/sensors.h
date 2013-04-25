// =============================================================================
// The driver for 4 dry contact sensors SENSOR0..SENSOR3 (normally reading 0).
// All sensors must be connected to the same port SENSORS.
// =============================================================================

#ifndef __DRIVERS__IN__SENSORS_H
#define __DRIVERS__IN__SENSORS_H

#include "cpu/avr/gpio.h"

#define SENSORS__MASK (SIGNAL_MASK(SENSOR0) | SIGNAL_MASK(SENSOR1) | SIGNAL_MASK(SENSOR2) | SIGNAL_MASK(SENSOR3))


struct sensors__status {
    uint8_t state;
    uint8_t prev_state;
};
extern struct sensors__status sensors__status;


inline uint8_t sensors__read(void) {
    return IN(SENSORS) & SENSORS__MASK;
}


inline void sensors__init(void) {
    ENABLE_PULLUP(SENSOR0);
    ENABLE_PULLUP(SENSOR1);
    ENABLE_PULLUP(SENSOR2);
    ENABLE_PULLUP(SENSOR3);
}

void sensors__run(void);

/**
 * Callback function, called by sensors__run() when any of the sensors has changed state.
 */
void sensors__status__on_change(void);

#endif
