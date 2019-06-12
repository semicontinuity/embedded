// =============================================================================
// Driver for encoder 2
// =============================================================================
#include "drivers/in/encoder2.h"
#include "drivers/in/encoder__step.h"
#include <cpu/avr/asm.h>
#include <cpu/avr/gpio.h>


#if CONCAT(0x, IN__ENCODER2__A__PORT) != CONCAT(0x, IN__ENCODER2__B__PORT)
#error "Pins of encoder 2 must be on the same port!"
#endif

#ifdef ENCODER2__STATE__REG
register volatile uint8_t encoder2__state asm(QUOTE(ENCODER2__STATE__REG));
#else
volatile uint8_t encoder2__state;
#endif

void encoder2__init(void) {
    USE_AS_INPUT(IN__ENCODER2__A);
    ENABLE_PULLUP(IN__ENCODER2__A);
    USE_AS_INPUT(IN__ENCODER2__B);
    ENABLE_PULLUP(IN__ENCODER2__B);

    encoder2__debounce_timer__init();
}

void encoder2__run(void) {
    if (!encoder2__debounce_timer__is_started()) {
        uint8_t raw_port_value = IN(IN__ENCODER2__A);
        uint8_t current_state = __builtin_avr_insert_bits(
            avr_insert_bits_map(
                0xF, // unaltered bit 7 from the last argument (0)
                0xF, // unaltered bit 6 from the last argument (0)
                0xF, // unaltered bit 5 from the last argument (0)
                0xF, // unaltered bit 4 from the last argument (0)
                0xF, // unaltered bit 3 from the last argument (0)
                0xF, // unaltered bit 2 from the last argument (0)
                IN__ENCODER2__A__PIN,
                IN__ENCODER2__B__PIN),
            raw_port_value,
            0
        );
        uint8_t index = (uint8_t) (encoder2__state << 2U) | current_state;
        encoder2__state = current_state;
        uint8_t delta = encoder__step[index];
        if (delta) {
            encoder2__handle_rotation_event(delta);
            encoder2__debounce_timer__start();
        }
    }
}
