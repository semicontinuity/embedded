#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"
#include "cpu/avr/drivers/display/mt12232/terminal.h"


const char LINE[] PROGMEM = "Hello,\nworld!\n";


int main(int argc, char **argv) {

    // backlight
    DDRD |= (1<<0);
    PORTD |= (1<<0);


    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    LCDG_InitPort();
    _delay_ms(30);  // takes longer?
    LCDG_InitLcd();
    LCDG_ClrAllDisp();

//    LCDG_SendString(0, 2, "Hello, world!");
/*
    LCDG_DrawLine(40,4, 70, 20);
    LCDG_DrawCircle(20, 11, 10);  
    LCDG_DrawRect(80, 4, 110, 19, FILL_OFF);
*/
//    LCDG_SendSymbol(2,0,'0');
//    LCDG_SendSymbol(2,1,'1');
//    LCDG_SendSymbol(2,2,'2');
//    LCDG_SendSymbol(2,3,'3');
    terminal__init();
    terminal__print_P(LINE);

    // TX
    DDRD |= (1<<3);
    PORTD |= (1<<3);

    // RTS
    DDRD |= (1<<6);
    PORTD &= ~(1<<6);

    // CTS
//    DDRD |= (1<<7);
//    PORTD &= ~(1<<7);

    while(1);
    return 0;
}
