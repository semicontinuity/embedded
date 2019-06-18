#include "cpu/avr/services/keyboard/keyboard.h"
#include "cpu/avr/services/keyboard/keyboard__port_d__encoders.h"
#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.h"
#include <cpu/avr/asm.h>


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1


inline void keyboard__port_d__encoders__process_encoder(uint8_t state, uint8_t changes, uint8_t encoder) {
}


void keyboard__port_d__encoders__process(uint8_t state, uint8_t changes) {
    __asm__ __volatile__("keyboard__port_d__encoders__process_encoder__3:");
    keyboard__port_d__encoders__process_encoder(state, changes, 3);
    __asm__ __volatile__("keyboard__port_d__encoders__process_encoder__2:");
    keyboard__port_d__encoders__process_encoder(state, changes, 2);
    __asm__ __volatile__("keyboard__port_d__encoders__process_encoder__1:");
    keyboard__port_d__encoders__process_encoder(state, changes, 1);
    __asm__ __volatile__("keyboard__port_d__encoders__process_encoder__0:");
    keyboard__port_d__encoders__process_encoder(state, changes, 0);
}

#endif
