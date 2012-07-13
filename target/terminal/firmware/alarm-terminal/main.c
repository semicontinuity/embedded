#include "device.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <compat/deprecated.h>

#include "keypad.h"
#include "password-processing.h"
#include "lcd_backlight_service.h"

#include "cpu/avr/drivers/display/mt12864/terminal.h"
#include "cpu/avr/drivers/display/mt12864/text-output.h"



uint8_t stateChangePulseTimeout = 0;

void state_change_pulse_start(void)
{
    state_change_low();
    stateChangePulseTimeout = 100;
}

void state_change_pulse_run(void)
{
    if (stateChangePulseTimeout != 0) // generating pulse
    {
        --stateChangePulseTimeout;
        if (stateChangePulseTimeout == 0) // just reached 0 - pulse generated
        {
            state_change_high();
        }
    }
}




void keyEvent (uint8_t keyevent)
{
    handlePasswordEntryEvent (keyevent);
    lcd_backlight_service__signal();
}


void passwordCharTyped(uint8_t c)
{
    terminal_displayChar('*');
}

const char MSG_PASSWORD_NOT_ACCEPTED[] PROGMEM = "\nНеверный код\n";
void incorrectPasswordEntered (void)
{
    lcd_print_string_progmem (MSG_PASSWORD_NOT_ACCEPTED);
}

const char MSG_PASSWORD_ACCEPTED[] PROGMEM = "\nКод принят\n";
void correctPasswordEntered (void)
{
    lcd_print_string_progmem (MSG_PASSWORD_ACCEPTED);
    state_change_pulse_start();
}


uint8_t alarm_state = 0;
uint8_t alarm_state_change_timeout = 0;
const char MSG_ARMED[] PROGMEM = "Поставлено на охрану\n";
const char MSG_DISARMED[] PROGMEM = "Снято с охраны\n";


/**
 * This interrupt is invoked F_CPU/1024/256 times per second.
 * (e.g. 45.5 / sec @ 12 MHz)
 */
ISR(PERIODIC_INTERRUPT_VECT)
{       
    wdt_reset();

    keypad__run(); // contains delay!
    lcd_backlight_service__run();
    state_change_pulse_run();

    // need to filter out noise that can be caused by mains transients
    if (alarm_state_change_timeout != 0)
    {
        --alarm_state_change_timeout;
        if (alarm_state_change_timeout == 0)
        {
            uint8_t new_alarm_state = is_system_armed();
            if (new_alarm_state != alarm_state)
            {
                const char* message;
                if (new_alarm_state)
                {
                    armed_led_on();
                    message = MSG_ARMED;
                }
                else
                {
                    armed_led_off();
                    message = MSG_DISARMED;
                }

                alarm_state = new_alarm_state;
                lcd_print_string_progmem (message);
            }
        }
    }
}


/**
 * This interrupt is invoked when the base station changes the state of alarm system.
 */
ISR(ALARM_STATE_INTERRUPT_VECT)
{   
    // start filtering out noise that can be caused by mains transients
    alarm_state_change_timeout = 5; // about 105 msec
}


const char MSG_READY[] PROGMEM = "\nГотов\n";
int main(void)
{
    wdt_enable (WDTO_2S);

    lcd_backlight_service__init();
    terminal_init();
    keypad__init();

    sensors_init();

    configure_io();
    configure_ext_interrupts();

    init_and_start_scheduler();



    lcd_print_string_progmem (MSG_READY);

    sei();

    return 0;
}
