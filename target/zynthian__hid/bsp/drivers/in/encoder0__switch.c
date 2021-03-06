#include "drivers/in/encoder0__switch.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#ifdef ENCODER0__SWITCH__STATE__REG
register volatile uint8_t encoder0__switch__state asm(QUOTE(ENCODER0__SWITCH__STATE__REG));
#else
volatile uint8_t encoder0__switch__state;
#endif


void encoder0__switch__init(void) {
    USE_AS_INPUT(IN__ENCODER0__SWITCH);
    ENABLE_PULLUP(IN__ENCODER0__SWITCH);
    encoder0__switch__state = (1U << IN__ENCODER0__SWITCH__PIN);    // depressed

    encoder0__switch__debounce_timer__init();
}

void encoder0__switch__run(void) {
    __asm__ __volatile__("encoder0__switch__run:");
    if (!encoder0__switch__debounce_timer__is_started()) {
        uint8_t raw_port_value = IN(IN__ENCODER0__SWITCH);
        uint8_t masked_port_value = raw_port_value & (1U << IN__ENCODER0__SWITCH__PIN);

        if (masked_port_value != encoder0__switch__state) {
            encoder0__switch__state = masked_port_value;
            encoder0__switch__handle_event(masked_port_value, IN__ENCODER0__SWITCH__PIN);
            encoder0__switch__debounce_timer__start();
        }
    }
}
