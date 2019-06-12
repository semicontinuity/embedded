#include "drivers/in/encoder3__switch.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#ifdef ENCODER3__SWITCH__STATE__REG
register volatile uint8_t encoder3__switch__state asm(QUOTE(ENCODER3__SWITCH__STATE__REG));
#else
volatile uint8_t encoder3__switch__state;
#endif


void encoder3__switch__init(void) {
    USE_AS_INPUT(IN__ENCODER3__SWITCH);
    ENABLE_PULLUP(IN__ENCODER3__SWITCH);
    encoder3__switch__state = (1U << IN__ENCODER3__SWITCH__PIN);    // depressed

    encoder3__switch__debounce_timer__init();
}

void encoder3__switch__run(void) {
    __asm__ __volatile__("encoder3__switch__run:");
    if (!encoder3__switch__debounce_timer__is_started()) {
        uint8_t raw_port_value = IN(IN__ENCODER3__SWITCH);
        uint8_t masked_port_value = raw_port_value & (1U << IN__ENCODER3__SWITCH__PIN);

        if (masked_port_value != encoder3__switch__state) {
            encoder3__switch__state = masked_port_value;
            encoder3__switch__handle_event(masked_port_value, IN__ENCODER3__SWITCH__PIN);
            encoder3__switch__debounce_timer__start();
        }
    }
}
