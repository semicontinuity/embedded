#include "drivers/in/encoder2__switch.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#ifdef ENCODER2__SWITCH__STATE__REG
register volatile uint8_t encoder2__switch__state asm(QUOTE(ENCODER2__SWITCH__STATE__REG));
#else
volatile uint8_t encoder2__switch__state;
#endif


void encoder2__switch__init(void) {
    USE_AS_INPUT(IN__ENCODER2__SWITCH);
    ENABLE_PULLUP(IN__ENCODER2__SWITCH);
    encoder2__switch__state = (1U << IN__ENCODER2__SWITCH__PIN);    // depressed

    encoder2__switch__debounce_timer__init();
}

void encoder2__switch__run(void) {
    __asm__ __volatile__("encoder2__switch__run:");
    if (!encoder2__switch__debounce_timer__is_started()) {
        uint8_t raw_port_value = IN(IN__ENCODER2__SWITCH);
        uint8_t masked_port_value = raw_port_value & (1U << IN__ENCODER2__SWITCH__PIN);

        if (masked_port_value != encoder2__switch__state) {
            encoder2__switch__state = masked_port_value;
            encoder2__switch__handle_event(masked_port_value, IN__ENCODER2__SWITCH__PIN);
            encoder2__switch__debounce_timer__start();
        }
    }
}
