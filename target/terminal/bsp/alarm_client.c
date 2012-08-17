#include <avr/interrupt.h>

#include "led.h"
#include "alarm_state.h"
#include "cpu/avr/drivers/display/mt12864/terminal.h"


uint8_t alarm_state;
uint8_t alarm_state_change_timeout;

const char MSG_ARMED[] PROGMEM = "Поставлено на охрану\n";
const char MSG_DISARMED[] PROGMEM = "Снято с охраны\n";


/**
 * This interrupt is invoked when the base station changes the state of alarm system.
 */
ISR(ALARM_STATE_INTERRUPT_VECT) {   
    // start filtering out noise that can be caused by mains transients
    alarm_state_change_timeout = ALARM_CLIENT__DEBOUNCE_TIME;
}


void alarm_client__run(void) {
    // need to filter out noise that can be caused by mains transients
    if (alarm_state_change_timeout != 0)
    {
        --alarm_state_change_timeout;
        if (alarm_state_change_timeout == 0)
        {
            uint8_t new_alarm_state = alarm_state__get();
            if (new_alarm_state != alarm_state)
            {
                const char* PROGMEM message;
                if (new_alarm_state)
                {
                    led__on();
                    message = MSG_ARMED;
                }
                else
                {
                    led__off();
                    message = MSG_DISARMED;
                }

                alarm_state = new_alarm_state;
                lcd_print_string_progmem (message);
            }
        }
    }
}
