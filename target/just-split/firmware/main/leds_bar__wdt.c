#include <avr/interrupt.h>
#include <services/gp_buffer.h>
//#include "leds_bar__data.h"


ISR(WDT_vect) {
    __asm__ __volatile__("WDT_vect:");
    gp_buffer__start();
//    leds_bar__data__put_position_reset();
}
