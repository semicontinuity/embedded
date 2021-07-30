#include "cpu/avr/services/keyboard/keyboard.h"
#include "cpu/avr/services/keyboard/keyboard__port_f__buttons.h"
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
#include "cpu/avr/services/keyboard/keyboard__port_f__encoders.h"
#endif

#include "cpu/avr/drivers/keyboard/keyboard__port_f__pins.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_f__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_f__debounce_timer.h"

#include <cpu/avr/asm.h>

#include <services/tracer.h>


#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1

#ifdef KEYBOARD__PORT_F__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_f__previous_state asm(QUOTE(KEYBOARD__PORT_F__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_f__previous_state;
#endif


void keyboard__port_f__init_previous_state(void) {
    __asm__ __volatile__("keyboard__port_f__init_previous_state:");
    keyboard__port_f__previous_state = keyboard__pins__port_f__pins_mask();
}

void keyboard__port_f__previous_state__copy_bit(const uint8_t state, const uint8_t bit) {
    COPY_BIT(state, bit, keyboard__port_f__previous_state, bit);
}


#ifdef KEYBOARD__PORT_F__MASK__REG
register volatile uint8_t keyboard__port_f__mask asm(QUOTE(KEYBOARD__PORT_F__MASK__REG));
#else
volatile uint8_t keyboard__port_f__mask;
#endif

void keyboard__port_f__mask__and_with(const uint8_t mask) {
    if (mask != 0xFF) {
        ANDI(keyboard__port_f__mask, mask & 0xFF);
    }
}

void keyboard__port_f__mask__clear_bit(const uint8_t bit) {
//    keyboard__port_f__mask__and_with(~((uint8_t) (1U << bit)));
}



void keyboard__port_f__mask__reset(void) {
#ifdef KEYBOARD__COMMON_MASK__REG
    MOV(keyboard__port_f__mask, keyboard__common_mask);
#else
    keyboard__port_f__mask = keyboard__pins__port_f__button_pins_mask();
#endif
}


void keyboard__port_f__run(void) {
    __asm__ __volatile__("keyboard__port_f__run:");
    uint8_t state = keyboard__pins__port_f__read();
    uint8_t changes = keyboard__port_f__mask & ((uint8_t) (keyboard__port_f__previous_state ^ state));
    if (changes) {
        keyboard__port_f__debounce_timer__start();
        tracer__keyboard__changes(0, changes);
        keyboard__port_f__mask ^= changes;
        keyboard__port_f__previous_state = state;
        keyboard__port_f__buttons__process(state, changes);
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
        keyboard__port_f__encoders__process(state, changes);
#endif
    }
}

#endif
