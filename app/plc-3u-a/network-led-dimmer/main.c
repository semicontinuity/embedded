#include <avr/interrupt.h>

#include "device.h"

#include "platform/plc-3u-a/can.h"
#include "platform/plc-3u-a/pwm.h"
#include "console_service.h"
#include "can_service.h"

//__attribute__ ((noreturn))
int main(void)
{
    console_service__init();

    pwm__init();
    pwm__start();

    spi__init();

    can__init();
    can__start();

    can_service__init();
    can_service__start();

    sei();
    console_service__run();
}
