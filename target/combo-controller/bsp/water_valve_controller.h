// =============================================================================
// Water valve controller service.
// =============================================================================

#ifndef __WATER_VALVE_CONTROLLER_H
#define __WATER_VALVE_CONTROLLER_H

#include <stdint.h>
#include "water_valve.h"


/**
 * Valid values for water_valve_controller__value.
 */
typedef enum {
    WATER_VALVE_CONTROLLER__VALUE__OPENED            = 0,
    WATER_VALVE_CONTROLLER__VALUE__CLOSED            = 1
} water_valve_controller__value_t;

/**
 * Valve value.
 */
extern water_valve_controller__value_t water_valve_controller__value;


INLINE void water_valve_controller__value__on_change(void);


inline static void water_valve_controller__set_value(uint8_t value) {
    if (value == WATER_VALVE_CONTROLLER__VALUE__OPENED) {
        water_valve__off();
    }
    else {
        water_valve__on();
    }

    water_valve_controller__value = value;
    water_valve_controller__value__on_change();
}

/**
 * Sets the desired valve value.
 */
inline static void water_valve_controller__value__set_from_raw_ptr(const void* ptr) {
    const water_valve_controller__value_t *value_ptr = (const water_valve_controller__value_t *)ptr;
    water_valve_controller__set_value(*value_ptr);
}

inline void water_valve_controller__init(void) {
}


#endif