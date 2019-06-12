// =============================================================================
// Driver for encoder 3
// =============================================================================
#include "drivers/in/encoder3.h"
#include "drivers/in/encoder__step.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#if CONCAT(0x, IN__ENCODER3__A__PORT) != CONCAT(0x, IN__ENCODER3__B__PORT)
#error "Pins of encoder 2 must be on the same port!"
#endif

#ifdef ENCODER3__STATE__REG
register volatile uint8_t encoder3__state asm(QUOTE(ENCODER3__STATE__REG));
#else
volatile uint8_t encoder3__state;
#endif

void encoder3__init(void) {
    __asm__ __volatile__("encoder3__init:");
    USE_AS_INPUT(IN__ENCODER3__A);
    ENABLE_PULLUP(IN__ENCODER3__A);
    USE_AS_INPUT(IN__ENCODER3__B);
    ENABLE_PULLUP(IN__ENCODER3__B);

    encoder3__debounce_timer__init();
}

void encoder3__run(void) {
    __asm__ __volatile__("encoder3__run:");
    if (!encoder3__debounce_timer__is_started()) {
        uint8_t raw_port_value = IN(IN__ENCODER3__A);
        uint8_t current_state = __builtin_avr_insert_bits(
            avr_insert_bits_map(
                0xF, // unaltered bit 7 from the last argument (0)
                0xF, // unaltered bit 6 from the last argument (0)
                0xF, // unaltered bit 5 from the last argument (0)
                0xF, // unaltered bit 4 from the last argument (0)
                0xF, // unaltered bit 3 from the last argument (0)
                0xF, // unaltered bit 2 from the last argument (0)
                IN__ENCODER3__A__PIN,
                IN__ENCODER3__B__PIN),
            raw_port_value,
            0
        );
        uint8_t index = (uint8_t) (encoder3__state << 2U) | current_state;
        encoder3__state = current_state;
        uint8_t delta = encoder__step[index];
        if (delta) {
            encoder3__handle_event(delta);
            encoder3__debounce_timer__start();
        }
    }
}
