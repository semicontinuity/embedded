#ifndef __SERVICES__WATER_LEAK_HANDLER_H
#define __SERVICES__WATER_LEAK_HANDLER_H

// =============================================================================
// Water leak handler service.
// - Listens for water leak sensors
// - Activates water valve
// - Turns on siren
// - Sends SMS notification
// =============================================================================

#include "water_leak_sensors_scanner.h"
#include "services/water_leak_handler__timer.h"

#include "drivers/out/siren1.h"
#include "drivers/out/water_valve.h"

#include "endpoints/comm__binary__0.h"
#include "endpoints/emergency__water_actuators__0.h"

#include <stdbool.h>
#include <avr/eeprom.h>


uint8_t EEMEM ee__water_leak_handler__action__enabled = WATER_LEAK_HANDLER__ACTION__ENABLED;
uint8_t water_leak_handler__action__enabled;

uint8_t EEMEM ee__water_leak_handler__sms__enabled = WATER_LEAK_HANDLER__SMS__ENABLED;
uint8_t water_leak_handler__sms__enabled;

uint8_t EEMEM ee__water_leak_handler__sound__duration = WATER_LEAK_HANDLER__SOUND__DURATION;
uint8_t water_leak_handler__sound__duration;


inline static void water_leak_handler__init(void) {
    water_leak_handler__action__enabled = eeprom_read_byte(&ee__water_leak_handler__action__enabled);
    water_leak_handler__sms__enabled = eeprom_read_byte(&ee__water_leak_handler__sms__enabled);
    water_leak_handler__sound__duration = eeprom_read_byte(&ee__water_leak_handler__sound__duration);
}


inline void water_leak_handler__sound__set(const bool on) {
    siren1__set(on);
    comm__binary__0__broadcast();
}

inline void water_leak_handler__water_valve__set(const bool on) {
    water_valve__set(on);
    emergency__water_actuators__0__broadcast();
}


/** Invoked by water_leak_sensors_scanner__run() when the state of water leak sensors has changed */
INLINE void water_leak_handler__run(void) {
    if (water_leak_handler__action__enabled && water_leak_sensors_scanner__is_active()) {
        if (water_leak_handler__action__enabled) {
            water_leak_handler__water_valve__set(1);  // not switched off automatically, must be switched off manually
        }
        if (ee__water_leak_handler__sound__duration) {
            water_leak_handler__sound__set(1); // switched off after timeout
            water_leak_handler__timer__set(ee__water_leak_handler__sound__duration);
        }
    }
}


INLINE void water_leak_handler__timer__output__run(void) {
    water_leak_handler__sound__set(0);
}

#endif
