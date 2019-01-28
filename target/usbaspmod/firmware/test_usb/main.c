// =============================================================================
// Test (blinking LEDs)
// =============================================================================

#include "drivers/out/led_green.h"
#include "drivers/out/led_red.h"

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

#include <usbdrv.h>


usbMsgLen_t usbFunctionSetup(uchar setupData[8])
{
	// cast to structured data for parsing
	usbRequest_t *request = (usbRequest_t*)(setupData);

	switch(request->bRequest)
	{
	case 0:
            led_red__set(request->wValue.bytes[0]);
	    return 0;
	case 1:
            led_green__set(request->wValue.bytes[0]);
	    return 0;
	}

	// ignore all unknown requests
	return 0;
}


int main(void) {
    led_red__init();
    led_green__init();

    for(;;) {
        led_red__set(0);
        led_green__set(1);
        _delay_ms(1000);

        led_red__set(1);
        led_green__set(0);
        _delay_ms(1000);
    }

    return 0;
}
