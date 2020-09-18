#include "cpu/avr/services/keyboard/keyboard.h"

#include "cpu/avr/services/keyboard/keyboard__port_a__buttons.h"
#include "cpu/avr/services/keyboard/keyboard__port_b__buttons.h"
#include "cpu/avr/services/keyboard/keyboard__port_c__buttons.h"
#include "cpu/avr/services/keyboard/keyboard__port_d__buttons.h"

#include "cpu/avr/services/keyboard/keyboard__port_a__encoders.h"
#include "cpu/avr/services/keyboard/keyboard__port_b__encoders.h"
#include "cpu/avr/services/keyboard/keyboard__port_c__encoders.h"
#include "cpu/avr/services/keyboard/keyboard__port_d__encoders.h"

#include "cpu/avr/drivers/keyboard/keyboard__pins.h"
#include "cpu/avr/drivers/keyboard/keyboard__debounce_timer.h"

#include "cpu/avr/drivers/keyboard/keyboard__port_a__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_b__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__pins__mapping.h"

#include "cpu/avr/drivers/keyboard/keyboard__port_a__debounce_timer.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_b__debounce_timer.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__debounce_timer.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__debounce_timer.h"

#include <cpu/avr/asm.h>

#include <services/tracer.h>


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#ifdef KEYBOARD__PORT_A__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_a__previous_state asm(QUOTE(KEYBOARD__PORT_A__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_a__previous_state;
#endif

void keyboard__port_a__previous_state__copy_bit(const uint8_t state, const uint8_t bit) {
    COPY_BIT(state, bit, keyboard__port_a__previous_state, bit);
}

#ifdef KEYBOARD__PORT_A__MASK__REG
register volatile uint8_t keyboard__port_a__mask asm(QUOTE(KEYBOARD__PORT_A__MASK__REG));
#else
volatile uint8_t keyboard__port_a__mask;
#endif

void keyboard__port_a__mask__and_with(const uint8_t mask) {
    if (mask != 0xFF) {
        ANDI(keyboard__port_a__mask, mask & 0xFF);
    }
}

void keyboard__port_a__mask__clear_bit(const uint8_t bit) {
//    keyboard__port_a__mask__and_with(~((uint8_t) (1U << bit)));
}


#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

#ifdef KEYBOARD__PORT_B__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_b__previous_state asm(QUOTE(KEYBOARD__PORT_B__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_b__previous_state;
#endif

void keyboard__port_b__previous_state__copy_bit(const uint8_t state, const uint8_t bit) {
    COPY_BIT(state, bit, keyboard__port_b__previous_state, bit);
}

#ifdef KEYBOARD__PORT_B__MASK__REG
register volatile uint8_t keyboard__port_b__mask asm(QUOTE(KEYBOARD__PORT_B__MASK__REG));
#else
volatile uint8_t keyboard__port_b__mask;
#endif

void keyboard__port_b__mask__and_with(const uint8_t mask) {
    if (mask != 0xFF) {
        ANDI(keyboard__port_b__mask, mask & 0xFF);
    }
}

void keyboard__port_b__mask__clear_bit(const uint8_t bit) {
//    keyboard__port_b__mask__and_with(~((uint8_t) (1U << bit)));
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

#ifdef KEYBOARD__PORT_C__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_c__previous_state asm(QUOTE(KEYBOARD__PORT_C__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_c__previous_state;
#endif

void keyboard__port_c__previous_state__copy_bit(const uint8_t state, const uint8_t bit) {
    COPY_BIT(state, bit, keyboard__port_c__previous_state, bit);
}

#ifdef KEYBOARD__PORT_C__MASK__REG
register volatile uint8_t keyboard__port_c__mask asm(QUOTE(KEYBOARD__PORT_C__MASK__REG));
#else
volatile uint8_t keyboard__port_c__mask;
#endif

void keyboard__port_c__mask__and_with(const uint8_t mask) {
    if (mask != 0xFF) {
        ANDI(keyboard__port_c__mask, mask & 0xFF);
    }
}

void keyboard__port_c__mask__clear_bit(const uint8_t bit) {
//    keyboard__port_c__mask__and_with(~((uint8_t) (1U << bit)));
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

#ifdef KEYBOARD__PORT_D__PREVIOUS_STATE__REG
register volatile uint8_t keyboard__port_d__previous_state asm(QUOTE(KEYBOARD__PORT_D__PREVIOUS_STATE__REG));
#else
volatile uint8_t keyboard__port_d__previous_state;
#endif

void keyboard__port_d__previous_state__copy_bit(const uint8_t state, const uint8_t bit) {
    COPY_BIT(state, bit, keyboard__port_d__previous_state, bit);
}

#ifdef KEYBOARD__PORT_D__MASK__REG
register volatile uint8_t keyboard__port_d__mask asm(QUOTE(KEYBOARD__PORT_D__MASK__REG));
#else
volatile uint8_t keyboard__port_d__mask;
#endif

void keyboard__port_d__mask__and_with(const uint8_t mask) {
    if (mask != 0xFF) {
        ANDI(keyboard__port_d__mask, mask & 0xFF);
    }
}

void keyboard__port_d__mask__clear_bit(const uint8_t bit) {
//    keyboard__port_d__mask__and_with(~((uint8_t) (1U << bit)));
}

#endif


#ifdef KEYBOARD__COMMON_MASK__REG
register volatile uint8_t keyboard__common_mask asm(QUOTE(KEYBOARD__COMMON_MASK__REG));
#endif


void keyboard__port_a__mask__reset(void) {
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
#ifdef KEYBOARD__COMMON_MASK__REG
    MOV(keyboard__port_a__mask, keyboard__common_mask);
#else
    keyboard__port_a__mask = keyboard__pins__port_a__button_pins_mask();
#endif
#endif
}

void keyboard__port_b__mask__reset(void) {
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
#ifdef KEYBOARD__COMMON_MASK__REG
    MOV(keyboard__port_b__mask, keyboard__common_mask);
#else
    keyboard__port_b__mask = keyboard__pins__port_b__button_pins_mask();
#endif
#endif
}

void keyboard__port_c__mask__reset(void) {
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
#ifdef KEYBOARD__COMMON_MASK__REG
    MOV(keyboard__port_c__mask, keyboard__common_mask);
#else
    keyboard__port_c__mask = keyboard__pins__port_c__button_pins_mask();
#endif
#endif
}

void keyboard__port_d__mask__reset(void) {
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
#ifdef KEYBOARD__COMMON_MASK__REG
    MOV(keyboard__port_d__mask, keyboard__common_mask);
#else
    keyboard__port_d__mask = keyboard__pins__port_d__button_pins_mask();
#endif
#endif
}


void keyboard__reset_masks(void) {
    keyboard__port_a__mask__reset();
    keyboard__port_b__mask__reset();
    keyboard__port_c__mask__reset();
    keyboard__port_d__mask__reset();
}


inline void keyboard__init_masks(void) {
    __asm__ __volatile__("keyboard__init_masks:");
#ifdef KEYBOARD__COMMON_MASK__REG
    uint8_t common_mask = 0;

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    common_mask |= keyboard__pins__port_a__button_pins_mask();
    common_mask |= keyboard__pins__port_a__encoders_pins_mask();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    common_mask |= keyboard__pins__port_b__button_pins_mask();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    common_mask |= keyboard__pins__port_c__button_pins_mask();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    common_mask |= keyboard__pins__port_d__button_pins_mask();
#endif

    common_mask |= keyboard__pins__port_b__encoders_pins_mask();
    common_mask |= keyboard__pins__port_c__encoders_pins_mask();
    common_mask |= keyboard__pins__port_d__encoders_pins_mask();

    keyboard__common_mask = common_mask;
#endif

    keyboard__reset_masks();
}


inline void keyboard__init_previous_states(void) {
    __asm__ __volatile__("keyboard__init_previous_states:");
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__previous_state = keyboard__pins__port_a__pins_mask();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__previous_state = keyboard__pins__port_b__pins_mask();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__previous_state = keyboard__pins__port_c__pins_mask();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__previous_state = keyboard__pins__port_d__pins_mask();
#endif
}


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

void keyboard__port_a__run(void) {
    __asm__ __volatile__("keyboard__port_a__run:");
    uint8_t state = keyboard__pins__port_a__read();
    uint8_t changes = keyboard__port_a__mask & ((uint8_t) (keyboard__port_a__previous_state ^ state));
    if (changes) {
        keyboard__port_a__debounce_timer__start();
        tracer__keyboard__changes(0, changes);
        keyboard__port_a__mask ^= changes;
        keyboard__port_a__previous_state = state;
        keyboard__port_a__buttons__process(state, changes);
        keyboard__port_a__encoders__process(state, changes);
    }
}

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

void keyboard__port_b__run(void) {
    __asm__ __volatile__("keyboard__port_b__run:");
    uint8_t state = keyboard__pins__port_b__read();
    uint8_t changes = keyboard__port_b__mask & ((uint8_t) (keyboard__port_b__previous_state ^ state));
    if (changes) {
        keyboard__port_b__debounce_timer__start();
        tracer__keyboard__changes(1, changes);
        keyboard__port_b__mask ^= changes;
        keyboard__port_b__previous_state = state;
        keyboard__port_b__buttons__process(state, changes);
        keyboard__port_b__encoders__process(state, changes);
    }
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

void keyboard__port_c__run(void) {
    __asm__ __volatile__("keyboard__port_c__run:");
    uint8_t state = keyboard__pins__port_c__read();
    uint8_t changes = keyboard__port_c__mask & ((uint8_t) (state ^ keyboard__port_c__previous_state));
    if (changes) {
        keyboard__port_c__debounce_timer__start();
        tracer__keyboard__changes(2, changes);
        keyboard__port_c__mask ^= changes;
        keyboard__port_c__previous_state = state;
        keyboard__port_c__buttons__process(state, changes);
        keyboard__port_c__encoders__process(state, changes);
    }
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

void keyboard__port_d__run(void) {
    __asm__ __volatile__("keyboard__port_d__run:");
    uint8_t state = keyboard__pins__port_d__read();
    uint8_t changes = keyboard__port_d__mask & ((uint8_t) (state ^ keyboard__port_d__previous_state));
    if (changes) {
        keyboard__port_d__debounce_timer__start();
        tracer__keyboard__changes(3, changes);
        keyboard__port_d__mask ^= changes;
        keyboard__port_d__previous_state = state;
        keyboard__port_d__buttons__process(state, changes);
        keyboard__port_d__encoders__process(state, changes);
    }
}

#endif


void keyboard__init_debounce_timers(void) {
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    __asm__ __volatile__("keyboard__port_a__debounce_timer__init:");
    keyboard__port_a__debounce_timer__init();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    __asm__ __volatile__("keyboard__port_b__debounce_timer__init:");
    keyboard__port_b__debounce_timer__init();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    __asm__ __volatile__("keyboard__port_c__debounce_timer__init:");
    keyboard__port_c__debounce_timer__init();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    __asm__ __volatile__("keyboard__port_d__debounce_timer__init:");
    keyboard__port_d__debounce_timer__init();
#endif
}


void keyboard__init(void) {
    keyboard__pins__init();
    keyboard__init_previous_states();
    keyboard__init_masks();
    keyboard__init_debounce_timers();
}


void keyboard__run(void) {
    __asm__ __volatile__("keyboard__run:");
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__run();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__run();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__run();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__run();
#endif
}
