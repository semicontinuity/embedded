#include <avr/interrupt.h>

#include "device.h"
#include "cpu/avr/gpio.h"
#include "cpu/avr/util/debug.h"

#include "platform/plc-3u-a/pwm.h"
#include "console_service.h"


__attribute__ ((noreturn))
int main(void)
{
    console_service__init();

    pwm__init();
    pwm__start();

    can_init();
    can_conf();
    can_start();

    sei();

    console_service__run();
}
