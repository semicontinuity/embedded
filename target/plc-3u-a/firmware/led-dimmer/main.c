#include "pwm.h"
#include <avr/interrupt.h>


int main(void) {
    colors[0] = 0;
    colors[1] = 50;
    colors[2] = 100;
    colors[3] = 150;
    colors[4] = 200;
    colors[5] = 255;


    pwm__init();
    pwm__start();

    sei();
    while(1);
    return 0;
}
