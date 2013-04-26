// =============================================================================
// Alarm handler service.
// - Listens for alarm events
// - Turns on siren
// - Sends SMS notification
// =============================================================================

#include "alarm.h"
#include "out/siren1.h"
#include "flags/siren1__changed.h"
#include "flags/notifications__pending.h"

#include <avr/eeprom.h>
#include <stdbool.h>


uint8_t EEMEM ee__alarm_handler__sound__enabled = ALARM_HANDLER__SOUND__ENABLED;
uint8_t alarm_handler__sound__enabled;

uint8_t EEMEM ee__alarm_handler__sms__enabled = ALARM_HANDLER__SMS__ENABLED;
uint8_t alarm_handler__sms__enabled;


inline static void alarm_handler__init(void) {
    alarm_handler__sound__enabled = eeprom_read_byte(&ee__alarm_handler__sound__enabled);
    alarm_handler__sms__enabled   = eeprom_read_byte(&ee__alarm_handler__sms__enabled);
}

// =============================================================================
// Implementation of callbacks from other modules (bindings)
// =============================================================================

void alarm__sound__set(const bool on) {
    if (alarm_handler__sound__enabled) {
        if (on) out__siren1__on(); else out__siren1__off();
        siren1__changed__set(1);
        notifications__pending__set(1);
    }
}


INLINE void alarm__state__on_change(void) {
    alarm__state__changed__set(1);
    notifications__pending__set(1);
}


/**
 * This procedure is called by alarm when it decided to notify about alarm condition.
 * It is called only once per session, not when alarm is switched on after it was mute.
 * Our reaction is to send SMS.
 */
INLINE void alarm__out__run(void) {    
}
