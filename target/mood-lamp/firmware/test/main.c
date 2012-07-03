#include "device.h"
#include "pwm.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>



#define CHANGE 20

void main(void)
{
    pwm__init();

        DRIVE_HIGH(LED_R);
        DRIVE_HIGH(LED_G);
        DRIVE_HIGH(LED_B);
_delay_ms(1000);

// R
        DRIVE_LOW(LED_R);
        DRIVE_HIGH(LED_G);
        DRIVE_HIGH(LED_B);
_delay_ms(1000);

// G
        DRIVE_HIGH(LED_R);
        DRIVE_LOW(LED_G);
        DRIVE_HIGH(LED_B);
_delay_ms(1000);

// B
        DRIVE_HIGH(LED_R);
        DRIVE_HIGH(LED_G);
        DRIVE_LOW(LED_B);



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
