#include "pwm.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>



#define CHANGE 20

void main(void)
{
    pwm__init();

        OUT_1(LED_R);
        OUT_1(LED_G);
        OUT_1(LED_B);
_delay_ms(1000);

// R
        OUT_0(LED_R);
        OUT_1(LED_G);
        OUT_1(LED_B);
_delay_ms(1000);

// G
        OUT_1(LED_R);
        OUT_0(LED_G);
        OUT_1(LED_B);
_delay_ms(1000);

// B
        OUT_1(LED_R);
        OUT_1(LED_G);
        OUT_0(LED_B);



        colors[0] = 255-0;	// R:0
        colors[1] = 255-255;	// G:255
        colors[2] = 255-0;	// B:0

    pwm__start();


    sei();


    for(;;) {
        uint8_t t;

        // COLOR: GREEN
        // -----------


        // increase blue
        t = 255;
        do {
cli();
            colors[2] = t;
sei();
            _delay_ms(CHANGE);
            --t;
        } while (t != 0);


        // COLOR: CYAN
        // -----------


        // decrease green
        t = 255;
        do {
cli();
            colors[1] = 255 - t;
sei();
           _delay_ms(CHANGE);
           --t;
        } while (t != 0);


        // COLOR: BLUE
        // -----------

        // increase green
        t = 255;
        do {
cli();
            colors[1] = t;
sei();
           _delay_ms(CHANGE);
           --t;
        } while (t != 0);


        // COLOR: CYAN
        // -----------

        // decrease blue
        t = 255;
        do {
cli();
            colors[2] = 255 - t;
sei();
            _delay_ms(CHANGE);
            --t;
        } while (t != 0);

    }
}
