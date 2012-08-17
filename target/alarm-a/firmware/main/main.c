#include "device.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "system_timer.h"
#include "sms.h"
#include "alarm.h"
#include "alarm_timer.h"
#include "unused.h"
#include "water_sensors.h"

#include "out_valve.h"
#include "out_buzzer.h"

#include "cpu/avr/usart0.h"


inline static void alarm__run(void) {    
    if (intruder_detected()) sensor_signal(); // makes sense to poll, to filter out noise
}


inline static void water_leak_detector__run(void) {    
    static uint8_t water_leak_detected = 0;
    if ((water_leak_detected == 0) && (water_sensor_a__is_active() || water_sensor_b__is_active())) {
        water_leak_detected = 1;
        valve__on();

        sendSms('5');
        wdt_reset(); // sending SMS may take a few seconds

        sendSms('6');
        wdt_reset(); // sending SMS may take a few seconds

//        sendSms('7');
//        sendSms('8');
    }
}


/**
 * This procedure is called by system timer periodically (every second).
 */
void system_timer__on_second_tick(void) {
    wdt_reset();
    water_leak_detector__run();
    alarm__run();
    alarm_timer__run();
}


/**
 * This procedure is called by system timer periodically (every system tick).
 */
void system_timer__on_system_tick(void) {
    // TODO: interrupt
    static uint8_t pwd_pulse = 0;
    if (pwd_entered()) {
        if (!pwd_pulse) {
            pwd_pulse = 1;
            correctPasswordEntered();
        }
    }
    else {
          /* It is faster just to set pwd_pulse to 0 unconditionally */
//        if (pwd_pulse)
//        {
            pwd_pulse = 0;
//        }
    }
}


/**
 * This procedure is called by alarm when it decided to notify about alarm condition.
 * It is called only once per session, not when alarm is switched on after it was mute.
 * Our reaction is to send SMS.
 */
void alarm_notification(void) {    
    sendSms('1');
    wdt_reset(); // sending SMS may take a few seconds

    sendSms('2');
    wdt_reset(); // sending SMS may take a few seconds

//    sendSms('3');
//    sendSms('4');
}


int main(void) {
    // maximal value, because sending SMS can take a few seconds
    // (SMSs are sent synchroniously)
    wdt_enable (WDTO_8S); 
    unused__init();

    // Debug/Mobile phone UART
    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();

    water_sensor_a__init();
    water_sensor_b__init();

    valve__init();
    buzzer__init();

    pwd_entered_pin_init();
    alarm_state_pin_init();
    sensor_line_pin_init();
    alarm_out_pin_init();

    system_timer__init();
    system_timer__start();
    
    // not used, alarm is 12V - will use for amplifier
    //switch_b_on();

    sei();
    while(1);
}
    