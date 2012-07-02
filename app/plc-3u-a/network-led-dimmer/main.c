#include <avr/interrupt.h>

#include "device.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/util/debug.h"

#include "dimmer.h"
#include "console_service.h"

//#include "mcp251x/struct.h"
//#include "mcp251x/registers.h"
//#include "mcp251x/operations.h"





__attribute__ ((noreturn))
int main(void)
{
    console_service__init();

    pwm_init();
    pwm_start();

    can_init();
    can_conf();
    can_start();

    sei();
//    while(1);    
    console_service__run();
//    return 0;
}
