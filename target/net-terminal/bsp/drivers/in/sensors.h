// =============================================================================
// The driver for 4 dry contact sensors SENSOR0..SENSOR3 (active low).
// The sensors must connected to the same port.
// =============================================================================

#ifndef __DRIVERS__IN__SENSORS_H
#define __DRIVERS__IN__SENSORS_H

#include "cpu/avr/gpio.h"

#define SENSORS__MASK (SIGNAL_MASK(SENSOR0) | SIGNAL_MASK(SENSOR1) | SIGNAL_MASK(SENSOR2) | SIGNAL_MASK(SENSOR3))


inline uint8_t sensors_read(void) {
    return IN(SENSORS) & SENSORS__MASK;
}


inline void sensors__init(void) {
    ENABLE_PULLUP(SENSOR0);
    ENABLE_PULLUP(SENSOR1);
    ENABLE_PULLUP(SENSOR2);
    ENABLE_PULLUP(SENSOR3);
}

#endif
