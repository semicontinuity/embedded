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

#include "drivers/out/water_valve.h"
#include "drivers/out/siren1.h"
#include "flags/siren1__changed.h"
#include "flags/notifications__pending.h"
#include "flags/water_valve__changed.h"
#include "flags/notifications__pending.h"

#include <stdbool.h>
#include <avr/eeprom.h>


uint8_t EEMEM ee__water_leak_handler__action__enabled = WATER_LEAK_HANDLER__ACTION__ENABLED;
uint8_t water_leak_handler__action__enabled;

uint8_t EEMEM ee__water_leak_handler__sms__enabled = WATER_LEAK_HANDLER__SMS__ENABLED;
uint8_t water_leak_handler__sms__enabled;

uint8_t EEMEM ee__water_leak_handler__sound__enabled = WATER_LEAK_HANDLER__SOUND__ENABLED;
uint8_t water_leak_handler__sound__enabled;


inline static void water_leak_handler__init(void) {
    water_leak_handler__action__enabled = eeprom_read_byte(&ee__water_leak_handler__action__enabled);
    water_leak_handler__sms__enabled = eeprom_read_byte(&ee__water_leak_handler__sms__enabled);
}


inline void water_leak_handler__sound__set(const bool on) {
    if (water_leak_handler__sound__enabled) {
        if (on) siren1__on(); else siren1__off();
        siren1__changed__set(1);
        notifications__pending__set(1);
    }
}


/** Invoked by water_leak_sensors_scanner__run() when the state of water leak sensors has changed */
INLINE void water_leak_handler__run(void) {
    if (water_leak_handler__action__enabled && water_leak_sensors_scanner__is_active()) {
        water_valve__on();  // not switched off automatically, must be switched off manually
    }
}

#endif
