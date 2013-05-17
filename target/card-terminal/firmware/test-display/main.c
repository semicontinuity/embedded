#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>

#include "cpu/avr/drivers/display/mt12232/lcd_graph_lib.h"


int main(int argc, char **argv) {

    MCUSR &= ~_BV(WDRF);
    wdt_disable();

    LCDG_InitPort();
    LCDG_InitLcd();
    LCDG_ClrAllDisp();
    LCDG_SendString(0, 3, "Hello, world!");
    LCDG_DrawLine(40,4, 70, 20);
    LCDG_DrawCircle(20, 11, 10);  
    LCDG_DrawRect(80, 4, 110, 19, FILL_OFF);

    while(1);
    return 0;
}
