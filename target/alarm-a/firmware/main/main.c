#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "system_timer.h"
#include "sms.h"
#include "alarm.h"
#include "alarm_timer.h"
#include "water_sensors.h"
#include "water_leak_detector.h"
#include "unused.h"

#include "in_pwd_entered.h"
#include "in_sensor_line.h"
#include "out_valve.h"
#include "out_buzzer.h"
#include "out_alarm_line.h"
#include "out_alarm_state_line.h"

#include "cpu/avr/usart0.h"

// =============================================================================
// Component bindings
// =============================================================================

/**
 * This procedure is called by alarm when it decided to notify about alarm condition.
 * It is called only once per session, not when alarm is switched on after it was mute.
 * Our reaction is to send SMS.
 */
void alarm__out__run(void) {    
    sms__send('1');
    wdt_reset(); // sending SMS may take a few seconds

    sms__send('2');
    wdt_reset(); // sending SMS may take a few seconds
}


/**
 * This procedure is called by water leak detector when it has decided to notify about the water leak.
 * Our reaction is to turn on valve and send SMS.
 */
void water_leak_detector__out__run(void) {    
    valve__on();

    sms__send('5');
    wdt_reset(); // sending SMS may take a few seconds

    sms__send('6');
    wdt_reset(); // sending SMS may take a few seconds
}


void sensor_line__on_active(void) {    
    alarm__sensor_active();
}

void pwd_entered__on_active(void) {    
    alarm__correct_password_entered();
}



void alarm__sound__on(void) {
    alarm_line__on();
    buzzer__on();
}

void alarm__sound__off(void) {
    alarm_line__off();
    buzzer__off();
}




/**
 * This procedure is called by system timer periodically (every second).
 */
void system_timer__on_second_tick(void) {
    wdt_reset();
    water_leak_detector__run();
    sensor_line__run();
    alarm_timer__run();
}


/**
 * This procedure is called by system timer periodically (every system tick).
 */
void system_timer__on_system_tick(void) {
    pwd_entered__run();
}


// =============================================================================
// Entry/Reset point
// =============================================================================

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

    pwd_entered__init();
    alarm_state_line__init();
    sensor_line__init();
    alarm_line__init();

    system_timer__init();
    system_timer__start();

    sei();
    while(1);
}
    