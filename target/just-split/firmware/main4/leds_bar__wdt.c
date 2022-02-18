#include <avr/interrupt.h>
#include "leds_bar__data.h"


ISR(WDT_vect) {
    leds_bar__data__put_position_reset();
}
