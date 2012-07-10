#include "device.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
// TODO remove
#include "alarm.h"

uint8_t fastCounter;
uint8_t counter;


/**
 * This ISR is invoked F_CPU/256/256 times per second (122 @ 8MHz)
 */
ISR(TIMER0_OVF_vect)
{   
    // TODO: interrupt
    static uint8_t pwd_pulse = 0;
    if (pwd_entered())
    {
        if (!pwd_pulse)
        {
            pwd_pulse = 1;
            correctPasswordEntered();
        }
    }
    else
    {
          /* It is faster just to set pwd_pulse to 0 unconditionally */
//        if (pwd_pulse)
//        {
            pwd_pulse = 0;
//        }
    }



    if (fastCounter != 0)
    {
        fastCounter--;
        return;
    }
    fastCounter = (F_CPU/256/256);

    // this place is invoked every 1s    
    process_periodic_event();


    // state transition after certain timeout only
    if (counter == 0) return;
    if (--counter == 0)
    {
        process_scheduled_event();
    }
}
    