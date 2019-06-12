#include "drivers/in/encoder1__switch.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#ifdef ENCODER1__SWITCH__STATE__REG
register volatile uint8_t encoder1__switch__state asm(QUOTE(ENCODER1__SWITCH__STATE__REG));
#else
volatile uint8_t encoder1__switch__state;
#endif


void encoder1__switch__init(void) {
    USE_AS_INPUT(IN__ENCODER1__SWITCH);
    ENABLE_PULLUP(IN__ENCODER1__SWITCH);
    encoder1__switch__state = (1U << IN__ENCODER1__SWITCH__PIN);    // depressed

    encoder1__switch__debounce_timer__init();
}

void encoder1__switch__run(void) {
    __asm__ __volatile__("encoder1__switch__run:");
    if (!encoder1__switch__debounce_timer__is_started()) {
        uint8_t raw_port_value = IN(IN__ENCODER1__SWITCH);
        uint8_t masked_port_value = raw_port_value & (1U << IN__ENCODER1__SWITCH__PIN);

        if (masked_port_value != encoder1__switch__state) {
            encoder1__switch__state = masked_port_value;
            encoder1__switch__handle_event(masked_port_value, IN__ENCODER1__SWITCH__PIN);
            encoder1__switch__debounce_timer__start();
        }
    }
}
