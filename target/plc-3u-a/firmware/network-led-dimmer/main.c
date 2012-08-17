#include <avr/interrupt.h>

#include "cpu/avr/spi.h"
#include "cpu/avr/drivers/net/can/mcp251x/conf.h"


#include "can.h"
#include "can_selector.h"

#include "pwm.h"
#include "console_service.h"
#include "can_service.h"

//__attribute__ ((noreturn))
int main(void)
{
    console_service__init();

    pwm__init();
    pwm__start();

    spi__init(SPI_CLKDIV_16);
    can_selector__init();

    mcp251x__init();

    can__init();
    can__start();

    can_service__init();
    can_service__start();

    sei();
    console_service__run();
}
