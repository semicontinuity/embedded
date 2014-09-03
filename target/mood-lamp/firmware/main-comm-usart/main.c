#include "pwm.h"
#include <avr/interrupt.h>

int main(void) {
    pwm__init();
    pwm__start();

    sei();
    for(;;) {
    }
    return 0;
}
