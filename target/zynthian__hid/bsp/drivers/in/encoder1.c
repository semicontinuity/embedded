// =============================================================================
// Driver for encoder 1
// =============================================================================
#include "drivers/in/encoder1.h"
#include "drivers/in/encoder__step.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#if CONCAT(0x, IN__ENCODER1__A__PORT) != CONCAT(0x, IN__ENCODER1__B__PORT)
#error "Pins of encoder 1 must be on the same port!"
#endif

#ifdef ENCODER1__STATE__REG
register volatile uint8_t encoder1__state asm(QUOTE(ENCODER1__STATE__REG));
#else
volatile uint8_t encoder1__state;
#endif


uint8_t encoder1__current_state() {
    uint8_t raw_port_value = IN(IN__ENCODER1__A);
    return __builtin_avr_insert_bits(
        avr_insert_bits_map(
            0xF, // unaltered bit 7 from the last argument (0)
            0xF, // unaltered bit 6 from the last argument (0)
            0xF, // unaltered bit 5 from the last argument (0)
            0xF, // unaltered bit 4 from the last argument (0)
            0xF, // unaltered bit 3 from the last argument (0)
            0xF, // unaltered bit 2 from the last argument (0)
            IN__ENCODER1__B__PIN,
            IN__ENCODER1__A__PIN),
        raw_port_value,
        0
    );
}

void encoder1__init(void) {
    __asm__ __volatile__("encoder1__init:");
    USE_AS_INPUT(IN__ENCODER1__A);
    ENABLE_PULLUP(IN__ENCODER1__A);
    USE_AS_INPUT(IN__ENCODER1__B);
    ENABLE_PULLUP(IN__ENCODER1__B);

    encoder1__debounce_timer__init();
}

void encoder1__start(void) {
    __asm__ __volatile__("encoder1__start:");
    encoder1__state = encoder1__current_state();
}

void encoder1__run(void) {
    __asm__ __volatile__("encoder1__run:");
    if (!encoder1__debounce_timer__is_started()) {
        uint8_t current_state = encoder1__current_state();
        uint8_t index = (uint8_t) (encoder1__state << 2U) | current_state;
        encoder1__state = current_state;
        uint8_t delta = encoder__step[index];
        if (delta) {
            encoder1__handle_event(delta);
            encoder1__debounce_timer__start();
        }
    }
}
