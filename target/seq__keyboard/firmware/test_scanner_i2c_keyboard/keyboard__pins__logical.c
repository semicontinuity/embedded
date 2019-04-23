#include "drivers/keyboard__pins.h"
#include "keyboard__pins__logical.h"
#include "cpu/avr/gpio.h"


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1

#ifdef KEYBOARD__PORT_A__STATE__REG
register volatile uint8_t keyboard__port_a__state asm(QUOTE(KEYBOARD__PORT_A__STATE__REG));
#else
volatile uint8_t keyboard__port_a__state;
#endif

void keyboard__pins__port_a__state__set(const uint8_t state) {
    keyboard__port_a__state = state;
}

uint8_t keyboard__pins__port_a__read(void) {
    return keyboard__port_a__state;
}

#endif


#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1

#ifdef KEYBOARD__PORT_B__STATE__REG
register volatile uint8_t keyboard__port_b__state asm(QUOTE(KEYBOARD__PORT_B__STATE__REG));
#else
volatile uint8_t keyboard__port_b__state;
#endif

void keyboard__pins__port_b__state__set(const uint8_t state) {
    keyboard__port_b__state = state;
}

uint8_t keyboard__pins__port_b__read(void) {
    return keyboard__port_b__state;
}

#endif


#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1

#ifdef KEYBOARD__PORT_C__STATE__REG
register volatile uint8_t keyboard__port_c__state asm(QUOTE(KEYBOARD__PORT_C__STATE__REG));
#else
volatile uint8_t keyboard__port_c__state;
#endif

void keyboard__pins__port_c__state__set(const uint8_t state) {
    keyboard__port_c__state = state;
}

uint8_t keyboard__pins__port_c__read(void) {
    return keyboard__port_c__state;
}

#endif


#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1

#ifdef KEYBOARD__PORT_D__STATE__REG
register volatile uint8_t keyboard__port_d__state asm(QUOTE(KEYBOARD__PORT_D__STATE__REG));
#else
volatile uint8_t keyboard__port_d__state;
#endif

void keyboard__pins__port_d__state__set(const uint8_t state) {
    keyboard__port_d__state = state;
}

uint8_t keyboard__pins__port_d__read(void) {
    return keyboard__port_d__state;
}

#endif



void keyboard__pins__init(void) {
    keyboard__pins__port_a__state__set(0xFF);
    keyboard__pins__port_b__state__set(0xFF);
    keyboard__pins__port_c__state__set(0xFF);
    keyboard__pins__port_d__state__set(0xFF);
}