//Atmega8A - используемый микроконтроллер
//#define F_CPU 8000000
#include <util/delay.h>
#include <stdlib.h>
//#include 
//объ€вим  библиотеку
#include "n5110.h"


#include "cpu/avr/gpio.h"
#include "cpu/avr/usart0.h"
#include "cpu/avr/usart0__rx_polled.h"


void application__init(void) {
    usart0__init();
}

void application__start(void) {
    usart0__rx__enabled__set(1);
}


char s_data[] = {' ', '\0'};
 
int main(void)
{

    DDRB |= _BV(5);
    application__init();
    application__start();

    Lcd_init();
    Lcd_clear();
    Lcd_rect_empty(0,0,83,41, PIXEL_ON);
    Lcd_print(0, 0, FONT_1X,(unsigned char *)s_data);
    Lcd_update();

    while(1)
    {
        uint8_t c = usart0__in__read();
        PINB |= _BV(5);
        s_data[0] = c;

        Lcd_clear();
        //Lcd_rect_empty(0,0,83,47, PIXEL_ON);
        Lcd_print(0, 0, FONT_1X,(unsigned char *)s_data);
        Lcd_update();
    }
}