// =============================================================================
// Water leak handler service.
// - Listens for water leak sensors
// - Activates water valve
// - Turns on siren
// - Sends SMS notification
// =============================================================================

#include <avr/eeprom.h>
#include "water_leak_sensors_scanner.h"
#include "out/water_valve.h"
#include "flags/water_valve__changed.h"
#include "flags/gpio_notifications__pending.h"

uint8_t EEMEM ee__water_leak_handler__enabled = WATER_LEAK_HANDLER__ENABLED;
uint8_t water_leak_handler__enabled;

inline static void water_leak_handler__init(void) {
    water_leak_handler__enabled = eeprom_read_byte(&ee__water_leak_handler__enabled);
}


/** Invoked by water_leak_sensors_scanner__run() when the state of water leak sensors has changed */
INLINE void water_leak_handler__run(void) {
    if (water_leak_handler__enabled && water_leak_sensors_scanner__is_active()) {
        out__water_valve__on();  // not switched off automatically, must be switched off manually
    }
}
