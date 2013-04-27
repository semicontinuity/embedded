#ifndef __SERVICES__ALARM_H
#define __SERVICES__ALARM_H

#include <stdint.h>
#include <avr/eeprom.h>


extern uint8_t EEMEM ee__alarm__time_arming;
extern uint8_t EEMEM ee__alarm__time_alert;
extern uint8_t EEMEM ee__alarm__time_alert_mute;
extern uint8_t EEMEM ee__alarm__time_alarm;
extern uint8_t EEMEM ee__alarm__time_alarm_mute;

extern uint8_t alarm__time_arming;
extern uint8_t alarm__time_alert;
extern uint8_t alarm__time_alert_mute;
extern uint8_t alarm__time_alarm;
extern uint8_t alarm__time_alarm_mute;


inline static void alarm__init(void) {
    alarm__time_arming     = eeprom_read_byte(&ee__alarm__time_arming);
    alarm__time_alert      = eeprom_read_byte(&ee__alarm__time_alert);
    alarm__time_alert_mute = eeprom_read_byte(&ee__alarm__time_alert_mute);
    alarm__time_alarm      = eeprom_read_byte(&ee__alarm__time_alarm);
    alarm__time_alarm_mute = eeprom_read_byte(&ee__alarm__time_alarm_mute);
}


enum alarm__state {
    // device is "disarmed" - ignores all events from sensor
    ALARM__STATE__DISARMED,

    // valid password was entered, device ignores events from sensor for TIME_ARMING
    ALARM__STATE__ARMING,

    // device is "armed", actively watching sensor. 
    ALARM__STATE__ARMED,

    // Sensor was active when alarm is in state ARMED, that is, intruder was detected.
    // If password is not until this state expires, alarm will be turned on.
    ALARM__STATE__ALERT,

    // valid password was not entered within TIME_ALERT. Alarm is turned on for TIME_ALARM
    ALARM__STATE__ALARM,

    // alarm was active for TIME_ALARM, now is muted for TIME_MUTE
    // after TIME_MUTE time, device goes to ALARM__STATE__ARMED state if there is no signal from sensor,
    // or immediately again
    ALARM__STATE__ALARM_MUTE,

    // device is "armed", actively watching sensor. 
    ALARM__STATE__ARMED_MUTE,

    // Sensor was active when alarm is in state ARMED_MUTE, that is, intruder was detected.
    // If password is not until this state expires, alarm will be turned on.
    ALARM__STATE__ALERT_MUTE
};

extern volatile enum alarm__state alarm__state;

// Alarm API
INLINE void alarm__arm(void);
INLINE void alarm__disarm(void);
INLINE void alarm__sensor_active(void);

// Alarm callbacks - to be implemented by user
INLINE void alarm__out__run(void);
INLINE void alarm__state__on_change(void);
void alarm__sound__set(const bool on);

#endif
    