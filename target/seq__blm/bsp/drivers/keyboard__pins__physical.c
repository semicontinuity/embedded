#include "drivers/keyboard__pins.h"

#include "drivers/in/button0.h"
#include "drivers/in/button1.h"
#include "drivers/in/button2.h"
#include "drivers/in/button3.h"
#include "drivers/in/button4.h"
#include "drivers/in/button5.h"
#include "drivers/in/button6.h"
#include "drivers/in/button7.h"
#include "drivers/in/button8.h"
#include "drivers/in/button9.h"
#include "drivers/in/button10.h"
#include "drivers/in/button11.h"
#include "drivers/in/button12.h"
#include "drivers/in/button13.h"
#include "drivers/in/button14.h"
#include "drivers/in/button15.h"


void keyboard__pins__init(void) {
    button0__init();
    button1__init();
    button2__init();
    button3__init();
    button4__init();
    button5__init();
    button6__init();
    button7__init();
    button8__init();
    button9__init();
    button10__init();
    button11__init();
    button12__init();
    button13__init();
    button14__init();
    button15__init();
}

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
uint8_t keyboard__pins__port_a__read(void) {
    return PINA;
}
#endif

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
uint8_t keyboard__pins__port_b__read(void) {
    return PINB;
}
#endif

#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
uint8_t keyboard__pins__port_c__read(void) {
    return PINC;
}
#endif

#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
uint8_t keyboard__pins__port_d__read(void) {
    return PIND;
}
#endif


/**
 * Provides pin number for the given button (if it pertains to port A)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_a__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xA
    if (button == 0) return IN__BUTTON0__PIN;
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xA
    if (button == 1) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xA
    if (button == 2) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xA
    if (button == 3) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xA
    if (button == 4) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xA
    if (button == 5) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xA
    if (button == 6) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xA
    if (button == 7) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xA
    if (button == 8) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xA
    if (button == 9) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xA
    if (button == 10) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xA
    if (button == 11) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xA
    if (button == 12) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xA
    if (button == 13) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xA
    if (button == 14) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xA
    if (button == 15) return IN__BUTTON15__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__pins__port_a__button_pins_mask(void) {
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xA
    mask |= (1 << (IN__BUTTON0__PIN));
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xA
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xA
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xA
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xA
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xA
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xA
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xA
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xA
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xA
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xA
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xA
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xA
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xA
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xA
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xA
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
    return mask;
}


/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_b__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xB
    if (button == 0) return IN__BUTTON0__PIN;
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xB
    if (button == 1) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xB
    if (button == 2) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xB
    if (button == 3) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xB
    if (button == 4) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xB
    if (button == 5) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xB
    if (button == 6) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xB
    if (button == 7) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xB
    if (button == 8) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xB
    if (button == 9) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xB
    if (button == 10) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xB
    if (button == 11) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xB
    if (button == 12) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xB
    if (button == 13) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xB
    if (button == 14) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xB
    if (button == 15) return IN__BUTTON15__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__pins__port_b__button_pins_mask(void) {
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xB
    mask |= (1 << (IN__BUTTON0__PIN));
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xB
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xB
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xB
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xB
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xB
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xB
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xB
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xB
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xB
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xB
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xB
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xB
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xB
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xB
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xB
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
    return mask;
}


/**
 * Provides pin number for the given button (if it pertains to port C)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_c__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xC
    if (button == 0) return IN__BUTTON0__PIN;
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xC
    if (button == 1) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xC
    if (button == 2) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xC
    if (button == 3) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xC
    if (button == 4) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xC
    if (button == 5) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xC
    if (button == 6) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xC
    if (button == 7) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xC
    if (button == 8) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xC
    if (button == 9) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xC
    if (button == 10) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xC
    if (button == 11) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xC
    if (button == 12) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xC
    if (button == 13) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xC
    if (button == 14) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xC
    if (button == 15) return IN__BUTTON15__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__pins__port_c__button_pins_mask(void) {
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON0__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON1__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON2__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON3__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON4__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON5__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON6__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON7__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON8__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON9__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON10__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON11__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON12__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON13__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON14__PIN)));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xC
    mask |= ((uint8_t)(1 << (IN__BUTTON15__PIN)));
#endif
    return mask;
}


/**
 * Provides pin number for the given button (if it pertains to port D)
 * @param button 0-15 for BUTTON0..BUTTON15
*/
uint8_t keyboard__pins__port_d__pin_for_button(const uint8_t button) {
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xD
    if (button == 0) return IN__BUTTON0__PIN;
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xD
    if (button == 1) return IN__BUTTON1__PIN;
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xD
    if (button == 2) return IN__BUTTON2__PIN;
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xD
    if (button == 3) return IN__BUTTON3__PIN;
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xD
    if (button == 4) return IN__BUTTON4__PIN;
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xD
    if (button == 5) return IN__BUTTON5__PIN;
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xD
    if (button == 6) return IN__BUTTON6__PIN;
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xD
    if (button == 7) return IN__BUTTON7__PIN;
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xD
    if (button == 8) return IN__BUTTON8__PIN;
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xD
    if (button == 9) return IN__BUTTON9__PIN;
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xD
    if (button == 10) return IN__BUTTON10__PIN;
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xD
    if (button == 11) return IN__BUTTON11__PIN;
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xD
    if (button == 12) return IN__BUTTON12__PIN;
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xD
    if (button == 13) return IN__BUTTON13__PIN;
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xD
    if (button == 14) return IN__BUTTON14__PIN;
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xD
    if (button == 15) return IN__BUTTON15__PIN;
#endif
    return 0xFF;
}


uint8_t keyboard__pins__port_d__button_pins_mask(void) {
    uint8_t mask = 0;
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xD
    mask |= (1 << (IN__BUTTON0__PIN));
#endif
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xD
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xD
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xD
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xD
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xD
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xD
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xD
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xD
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xD
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xD
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xD
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xD
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xD
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xD
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xD
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
    return mask;
}
