#include "keyboard__interrupts.h"
#include "cpu/avr/pin_change_int0.h"
#include "cpu/avr/pin_change_int1.h"
#include "cpu/avr/pin_change_int2.h"
#include "cpu/avr/gpio.h" // make macros.h

/**
 * Computes Pin Change Interrupt 0 mask for given button.
 * @param button 0-15 for BUTTON1..BUTTON16
*/
uint8_t pin_change_int0__mask_for_button(const uint8_t button) {
    // Pin Change Interrupt 0 serves PB0..PB7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xB
    if (button == 0) mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xB
    if (button == 1) mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xB
    if (button == 2) mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xB
    if (button == 3) mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xB
    if (button == 4) mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xB
    if (button == 5) mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xB
    if (button == 6) mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xB
    if (button == 7) mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xB
    if (button == 8) mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xB
    if (button == 9) mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xB
    if (button == 10) mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xB
    if (button == 11) mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xB
    if (button == 12) mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xB
    if (button == 13) mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xB
    if (button == 14) mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xB
    if (button == 15) mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


uint8_t pin_change_int0__mask(void) {
    // Pin Change Interrupt 0 serves PB0..PB7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xB
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xB
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xB
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xB
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xB
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xB
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xB
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xB
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xB
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xB
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xB
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xB
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xB
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xB
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xB
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xB
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


void pin_change_int0__init(void) {
    pin_change_int0__mask__set(pin_change_int0__mask());
}


/**
 * Computes Pin Change Interrupt 1 mask for given button.
 * @param button 0-15 for BUTTON1..BUTTON16
*/
uint8_t pin_change_int1__mask_for_button(const uint8_t button) {
    // Pin Change Interrupt 1 serves PC0..PC6
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xC
    if (button == 0) mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xC
    if (button == 1) mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xC
    if (button == 2) mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xC
    if (button == 3) mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xC
    if (button == 4) mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xC
    if (button == 5) mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xC
    if (button == 6) mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xC
    if (button == 7) mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xC
    if (button == 8) mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xC
    if (button == 9) mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xC
    if (button == 10) mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xC
    if (button == 11) mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xC
    if (button == 12) mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xC
    if (button == 13) mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xC
    if (button == 14) mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xC
    if (button == 15) mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


uint8_t pin_change_int1__mask(void) {
    // Pin Change Interrupt 1 serves PC0..PC6
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xC
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xC
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xC
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xC
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xC
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xC
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xC
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xC
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xC
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xC
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xC
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xC
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xC
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xC
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xC
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xC
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


void pin_change_int1__init(void) {
    pin_change_int1__mask__set(pin_change_int1__mask());
}


/**
 * Computes Pin Change Interrupt 2 mask for given button.
 * @param button 0-15 for BUTTON1..BUTTON16
*/
uint8_t pin_change_int2__mask_for_button(const uint8_t button) {
    // Pin Change Interrupt 2 serves PD0..PD7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xD
    if (button == 0) mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xD
    if (button == 1) mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xD
    if (button == 2) mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xD
    if (button == 3) mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xD
    if (button == 4) mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xD
    if (button == 5) mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xD
    if (button == 6) mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xD
    if (button == 7) mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xD
    if (button == 8) mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xD
    if (button == 9) mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xD
    if (button == 10) mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xD
    if (button == 11) mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xD
    if (button == 12) mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xD
    if (button == 13) mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xD
    if (button == 14) mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xD
    if (button == 15) mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}


uint8_t pin_change_int2__mask(void) {
    // Pin Change Interrupt 1 serves PD0..PD7
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON1__PORT)==0xD
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT)==0xD
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT)==0xD
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT)==0xD
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT)==0xD
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT)==0xD
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT)==0xD
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT)==0xD
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT)==0xD
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT)==0xD
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT)==0xD
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT)==0xD
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT)==0xD
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT)==0xD
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT)==0xD
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#if CONCAT(0x, IN__BUTTON16__PORT)==0xD
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
    return mask;
}

void pin_change_int2__init(void) {
    pin_change_int2__mask__set(pin_change_int2__mask());
}

void keyboard__interrupts__init(void) {
    pin_change_int0__init();
    pin_change_int1__init();
    pin_change_int2__init();
}

void keyboard__interrupts__start(void) {
    pin_change_int0__start();
    pin_change_int1__start();
    pin_change_int2__start();
}
