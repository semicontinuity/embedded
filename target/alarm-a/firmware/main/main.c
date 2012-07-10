#include "device.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "sms.h"
#include "alarm.h"

#include "cpu/avr/usart0.h"


/**
 * This procedure is called by scheduler periodically.
 */
void process_periodic_event(void)
{
    wdt_reset();

    static uint8_t water_leak_detected = 0;
    if ((water_leak_detected==0) && (water_leak_a() || water_leak_b()))
    {
        water_leak_detected = 1;
        switch_a_on();

        sendSms('5');
        wdt_reset(); // sending SMS may take a few seconds

        sendSms('6');
        wdt_reset(); // sending SMS may take a few seconds

//        sendSms('7');
//        sendSms('8');
    }

    if (intruder_detected()) sensor_signal(); // makes sense to poll, to filter out noise
}

/**
 * This procedure is called by alarm when it decided to notify about alarm condition.
 * It is called only once per session, not when alarm is switched on after it was mute.
 * Our reaction is to send SMS.
 */
void alarm_notification(void)
{    
    sendSms('1');
    wdt_reset(); // sending SMS may take a few seconds

    sendSms('2');
    wdt_reset(); // sending SMS may take a few seconds

//    sendSms('3');
//    sendSms('4');
}


int main(void)
{
    // maximal value, because sending SMS can take a few seconds
    // (SMSs are sent synchroniously)
    wdt_enable (WDTO_8S); 
    configure_unused_ports();

    // Debug/Mobile phone UART
    usart__pins_init();
    usart__rate__set(USART_BAUD_RATE);
    usart__init();
    usart__out__enabled__set();
    usart__in__enabled__set();

    water_sensor_a_init();
    water_sensor_b_init()

    switch_a_init();
    switch_b_init();

    pwd_entered_pin_init();
    alarm_state_pin_init();
    sensor_line_pin_init();
    alarm_out_pin_init();

    init_and_start_scheduler();
    
    // not used, alarm is 12V - will use for amplifier
    //switch_b_on();

    sei();
    while(1);
}
    