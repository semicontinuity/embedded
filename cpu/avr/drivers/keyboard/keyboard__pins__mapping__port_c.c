#include "cpu/avr/drivers/keyboard/keyboard__port_c__pins__mapping.h"
#include "cpu/avr/macros.h"


/**
 * Provides pin number for the given button (if it pertains to port C)
 * @param button 0-31 for BUTTON0..BUTTON31
*/
uint8_t keyboard__pins__port_c__pin_for_button(const uint8_t button) {
#if defined(IN__BUTTON0__PORT) && defined(IN__BUTTON0__PIN) && SINGLEQUOTED(IN__BUTTON0__PORT) == 'C'
    if (button == 0) return IN__BUTTON0__PIN;
#endif

#if defined(IN__BUTTON1__PORT) && defined(IN__BUTTON1__PIN) && SINGLEQUOTED(IN__BUTTON1__PORT) == 'C'
    if (button == 1) return IN__BUTTON1__PIN;
#endif

#if defined(IN__BUTTON2__PORT) && defined(IN__BUTTON2__PIN) && SINGLEQUOTED(IN__BUTTON2__PORT) == 'C'
    if (button == 2) return IN__BUTTON2__PIN;
#endif

#if defined(IN__BUTTON3__PORT) && defined(IN__BUTTON3__PIN) && SINGLEQUOTED(IN__BUTTON3__PORT) == 'C'
    if (button == 3) return IN__BUTTON3__PIN;
#endif

#if defined(IN__BUTTON4__PORT) && defined(IN__BUTTON4__PIN) && SINGLEQUOTED(IN__BUTTON4__PORT) == 'C'
    if (button == 4) return IN__BUTTON4__PIN;
#endif

#if defined(IN__BUTTON5__PORT) && defined(IN__BUTTON5__PIN) && SINGLEQUOTED(IN__BUTTON5__PORT) == 'C'
    if (button == 5) return IN__BUTTON5__PIN;
#endif

#if defined(IN__BUTTON6__PORT) && defined(IN__BUTTON6__PIN) && SINGLEQUOTED(IN__BUTTON6__PORT) == 'C'
    if (button == 6) return IN__BUTTON6__PIN;
#endif

#if defined(IN__BUTTON7__PORT) && defined(IN__BUTTON7__PIN) && SINGLEQUOTED(IN__BUTTON7__PORT) == 'C'
    if (button == 7) return IN__BUTTON7__PIN;
#endif

#if defined(IN__BUTTON8__PORT) && defined(IN__BUTTON8__PIN) && SINGLEQUOTED(IN__BUTTON8__PORT) == 'C'
    if (button == 8) return IN__BUTTON8__PIN;
#endif

#if defined(IN__BUTTON9__PORT) && defined(IN__BUTTON9__PIN) && SINGLEQUOTED(IN__BUTTON9__PORT) == 'C'
    if (button == 9) return IN__BUTTON9__PIN;
#endif

#if defined(IN__BUTTON10__PORT) && defined(IN__BUTTON10__PIN) && SINGLEQUOTED(IN__BUTTON10__PORT) == 'C'
    if (button == 10) return IN__BUTTON10__PIN;
#endif

#if defined(IN__BUTTON11__PORT) && defined(IN__BUTTON11__PIN) && SINGLEQUOTED(IN__BUTTON11__PORT) == 'C'
    if (button == 11) return IN__BUTTON11__PIN;
#endif

#if defined(IN__BUTTON12__PORT) && defined(IN__BUTTON12__PIN) && SINGLEQUOTED(IN__BUTTON12__PORT) == 'C'
    if (button == 12) return IN__BUTTON12__PIN;
#endif

#if defined(IN__BUTTON13__PORT) && defined(IN__BUTTON13__PIN) && SINGLEQUOTED(IN__BUTTON13__PORT) == 'C'
    if (button == 13) return IN__BUTTON13__PIN;
#endif

#if defined(IN__BUTTON14__PORT) && defined(IN__BUTTON14__PIN) && SINGLEQUOTED(IN__BUTTON14__PORT) == 'C'
    if (button == 14) return IN__BUTTON14__PIN;
#endif

#if defined(IN__BUTTON15__PORT) && defined(IN__BUTTON15__PIN) && SINGLEQUOTED(IN__BUTTON15__PORT) == 'C'
    if (button == 15) return IN__BUTTON15__PIN;
#endif

#if defined(IN__BUTTON16__PORT) && defined(IN__BUTTON16__PIN) && SINGLEQUOTED(IN__BUTTON16__PORT) == 'C'
    if (button == 16) return IN__BUTTON16__PIN;
#endif

#if defined(IN__BUTTON17__PORT) && defined(IN__BUTTON17__PIN) && SINGLEQUOTED(IN__BUTTON17__PORT) == 'C'
    if (button == 17) return IN__BUTTON17__PIN;
#endif

#if defined(IN__BUTTON18__PORT) && defined(IN__BUTTON18__PIN) && SINGLEQUOTED(IN__BUTTON18__PORT) == 'C'
    if (button == 18) return IN__BUTTON18__PIN;
#endif

#if defined(IN__BUTTON19__PORT) && defined(IN__BUTTON19__PIN) && SINGLEQUOTED(IN__BUTTON19__PORT) == 'C'
    if (button == 19) return IN__BUTTON19__PIN;
#endif

#if defined(IN__BUTTON20__PORT) && defined(IN__BUTTON20__PIN) && SINGLEQUOTED(IN__BUTTON20__PORT) == 'C'
    if (button == 20) return IN__BUTTON20__PIN;
#endif

#if defined(IN__BUTTON21__PORT) && defined(IN__BUTTON21__PIN) && SINGLEQUOTED(IN__BUTTON21__PORT) == 'C'
    if (button == 21) return IN__BUTTON21__PIN;
#endif

#if defined(IN__BUTTON22__PORT) && defined(IN__BUTTON22__PIN) && SINGLEQUOTED(IN__BUTTON22__PORT) == 'C'
    if (button == 22) return IN__BUTTON22__PIN;
#endif

#if defined(IN__BUTTON23__PORT) && defined(IN__BUTTON23__PIN) && SINGLEQUOTED(IN__BUTTON23__PORT) == 'C'
    if (button == 23) return IN__BUTTON23__PIN;
#endif

#if defined(IN__BUTTON24__PORT) && defined(IN__BUTTON24__PIN) && SINGLEQUOTED(IN__BUTTON24__PORT) == 'C'
    if (button == 24) return IN__BUTTON24__PIN;
#endif

#if defined(IN__BUTTON25__PORT) && defined(IN__BUTTON25__PIN) && SINGLEQUOTED(IN__BUTTON25__PORT) == 'C'
    if (button == 25) return IN__BUTTON25__PIN;
#endif

#if defined(IN__BUTTON26__PORT) && defined(IN__BUTTON26__PIN) && SINGLEQUOTED(IN__BUTTON26__PORT) == 'C'
    if (button == 26) return IN__BUTTON26__PIN;
#endif

#if defined(IN__BUTTON27__PORT) && defined(IN__BUTTON27__PIN) && SINGLEQUOTED(IN__BUTTON27__PORT) == 'C'
    if (button == 27) return IN__BUTTON27__PIN;
#endif

#if defined(IN__BUTTON28__PORT) && defined(IN__BUTTON28__PIN) && SINGLEQUOTED(IN__BUTTON28__PORT) == 'C'
    if (button == 28) return IN__BUTTON28__PIN;
#endif

#if defined(IN__BUTTON29__PORT) && defined(IN__BUTTON29__PIN) && SINGLEQUOTED(IN__BUTTON29__PORT) == 'C'
    if (button == 29) return IN__BUTTON29__PIN;
#endif

#if defined(IN__BUTTON30__PORT) && defined(IN__BUTTON30__PIN) && SINGLEQUOTED(IN__BUTTON30__PORT) == 'C'
    if (button == 30) return IN__BUTTON30__PIN;
#endif

#if defined(IN__BUTTON31__PORT) && defined(IN__BUTTON31__PIN) && SINGLEQUOTED(IN__BUTTON31__PORT) == 'C'
    if (button == 31) return IN__BUTTON31__PIN;
#endif

    return 0xFF;
}


uint8_t keyboard__pins__port_c__button_pins_mask(void) {
    uint8_t mask = 0;

#if defined(IN__BUTTON0__PORT) && defined(IN__BUTTON0__PIN)
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON0__PIN)));
#endif
#endif

#if defined(IN__BUTTON1__PORT) && defined(IN__BUTTON1__PIN)
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON1__PIN)));
#endif
#endif

#if defined(IN__BUTTON2__PORT) && defined(IN__BUTTON2__PIN)
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON2__PIN)));
#endif
#endif

#if defined(IN__BUTTON3__PORT) && defined(IN__BUTTON3__PIN)
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON3__PIN)));
#endif
#endif

#if defined(IN__BUTTON4__PORT) && defined(IN__BUTTON4__PIN)
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON4__PIN)));
#endif
#endif

#if defined(IN__BUTTON5__PORT) && defined(IN__BUTTON5__PIN)
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON5__PIN)));
#endif
#endif

#if defined(IN__BUTTON6__PORT) && defined(IN__BUTTON6__PIN)
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON6__PIN)));
#endif
#endif

#if defined(IN__BUTTON7__PORT) && defined(IN__BUTTON7__PIN)
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON7__PIN)));
#endif
#endif

#if defined(IN__BUTTON8__PORT) && defined(IN__BUTTON8__PIN)
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON8__PIN)));
#endif
#endif

#if defined(IN__BUTTON9__PORT) && defined(IN__BUTTON9__PIN)
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON9__PIN)));
#endif
#endif

#if defined(IN__BUTTON10__PORT) && defined(IN__BUTTON10__PIN)
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON10__PIN)));
#endif
#endif

#if defined(IN__BUTTON11__PORT) && defined(IN__BUTTON11__PIN)
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON11__PIN)));
#endif
#endif

#if defined(IN__BUTTON12__PORT) && defined(IN__BUTTON12__PIN)
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON12__PIN)));
#endif
#endif

#if defined(IN__BUTTON13__PORT) && defined(IN__BUTTON13__PIN)
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON13__PIN)));
#endif
#endif

#if defined(IN__BUTTON14__PORT) && defined(IN__BUTTON14__PIN)
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON14__PIN)));
#endif
#endif

#if defined(IN__BUTTON15__PORT) && defined(IN__BUTTON15__PIN)
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON15__PIN)));
#endif
#endif

#if defined(IN__BUTTON16__PORT) && defined(IN__BUTTON16__PIN)
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON16__PIN)));
#endif
#endif

#if defined(IN__BUTTON17__PORT) && defined(IN__BUTTON17__PIN)
#if CONCAT(0x, IN__BUTTON17__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON17__PIN)));
#endif
#endif

#if defined(IN__BUTTON18__PORT) && defined(IN__BUTTON18__PIN)
#if CONCAT(0x, IN__BUTTON18__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON18__PIN)));
#endif
#endif

#if defined(IN__BUTTON19__PORT) && defined(IN__BUTTON19__PIN)
#if CONCAT(0x, IN__BUTTON19__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON19__PIN)));
#endif
#endif

#if defined(IN__BUTTON20__PORT) && defined(IN__BUTTON20__PIN)
#if CONCAT(0x, IN__BUTTON20__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON20__PIN)));
#endif
#endif

#if defined(IN__BUTTON21__PORT) && defined(IN__BUTTON21__PIN)
#if CONCAT(0x, IN__BUTTON21__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON21__PIN)));
#endif
#endif

#if defined(IN__BUTTON22__PORT) && defined(IN__BUTTON22__PIN)
#if CONCAT(0x, IN__BUTTON22__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON22__PIN)));
#endif
#endif

#if defined(IN__BUTTON23__PORT) && defined(IN__BUTTON23__PIN)
#if CONCAT(0x, IN__BUTTON23__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON23__PIN)));
#endif
#endif

#if defined(IN__BUTTON24__PORT) && defined(IN__BUTTON24__PIN)
#if CONCAT(0x, IN__BUTTON24__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON24__PIN)));
#endif
#endif

#if defined(IN__BUTTON25__PORT) && defined(IN__BUTTON25__PIN)
#if CONCAT(0x, IN__BUTTON25__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON25__PIN)));
#endif
#endif

#if defined(IN__BUTTON26__PORT) && defined(IN__BUTTON26__PIN)
#if CONCAT(0x, IN__BUTTON26__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON26__PIN)));
#endif
#endif

#if defined(IN__BUTTON27__PORT) && defined(IN__BUTTON27__PIN)
#if CONCAT(0x, IN__BUTTON27__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON27__PIN)));
#endif
#endif

#if defined(IN__BUTTON28__PORT) && defined(IN__BUTTON28__PIN)
#if CONCAT(0x, IN__BUTTON28__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON28__PIN)));
#endif
#endif

#if defined(IN__BUTTON29__PORT) && defined(IN__BUTTON29__PIN)
#if CONCAT(0x, IN__BUTTON29__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON29__PIN)));
#endif
#endif

#if defined(IN__BUTTON30__PORT) && defined(IN__BUTTON30__PIN)
#if CONCAT(0x, IN__BUTTON30__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON30__PIN)));
#endif
#endif

#if defined(IN__BUTTON31__PORT) && defined(IN__BUTTON31__PIN)
#if CONCAT(0x, IN__BUTTON31__PORT) == 0xC
    mask |= ((uint8_t)(1U << (uint8_t)(IN__BUTTON31__PIN)));
#endif
#endif

    return mask;
}


/**
 * Provides pin number for the given encoder A pin (if it pertains to port C)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_c__pin_a_for_encoder(const uint8_t encoder) {
#if defined(IN__ENCODER0__A__PORT) && defined(IN__ENCODER0__A__PIN)
#if CONCAT(0x, IN__ENCODER0__A__PORT) == 0xC
    if (encoder == 0) return IN__ENCODER0__A__PIN;
#endif
#endif

#if defined(IN__ENCODER1__A__PORT) && defined(IN__ENCODER1__A__PIN)
#if CONCAT(0x, IN__ENCODER1__A__PORT) == 0xC
    if (encoder == 1) return IN__ENCODER1__A__PIN;
#endif
#endif

#if defined(IN__ENCODER2__A__PORT) && defined(IN__ENCODER2__A__PIN)
#if CONCAT(0x, IN__ENCODER2__A__PORT) == 0xC
    if (encoder == 2) return IN__ENCODER2__A__PIN;
#endif
#endif

#if defined(IN__ENCODER3__A__PORT) && defined(IN__ENCODER3__A__PIN)
#if CONCAT(0x, IN__ENCODER3__A__PORT) == 0xC
    if (encoder == 3) return IN__ENCODER3__A__PIN;
#endif
#endif

    return 0xFF;
}


/**
 * Provides pin number for the given encoder B pin (if it pertains to port C)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_c__pin_b_for_encoder(const uint8_t encoder) {
#if defined(IN__ENCODER0__B__PORT) && defined(IN__ENCODER0__B__PIN)
#if CONCAT(0x, IN__ENCODER0__B__PORT) == 0xC
    if (encoder == 0) return IN__ENCODER0__B__PIN;
#endif
#endif

#if defined(IN__ENCODER1__B__PORT) && defined(IN__ENCODER1__B__PIN)
#if CONCAT(0x, IN__ENCODER1__B__PORT) == 0xC
    if (encoder == 1) return IN__ENCODER1__B__PIN;
#endif
#endif

#if defined(IN__ENCODER2__B__PORT) && defined(IN__ENCODER2__B__PIN)
#if CONCAT(0x, IN__ENCODER2__B__PORT) == 0xC
    if (encoder == 2) return IN__ENCODER2__B__PIN;
#endif
#endif

#if defined(IN__ENCODER3__B__PORT) && defined(IN__ENCODER3__B__PIN)
#if CONCAT(0x, IN__ENCODER3__B__PORT) == 0xC
    if (encoder == 3) return IN__ENCODER3__B__PIN;
#endif
#endif

    return 0xFF;
}


uint8_t keyboard__pins__port_c__encoders_pins_mask(void) {
    uint8_t mask = 0;
    mask |= (1U << keyboard__pins__port_c__pin_a_for_encoder(0));
    mask |= (1U << keyboard__pins__port_c__pin_b_for_encoder(0));
    mask |= (1U << keyboard__pins__port_c__pin_a_for_encoder(1));
    mask |= (1U << keyboard__pins__port_c__pin_b_for_encoder(1));
    mask |= (1U << keyboard__pins__port_c__pin_a_for_encoder(2));
    mask |= (1U << keyboard__pins__port_c__pin_b_for_encoder(2));
    mask |= (1U << keyboard__pins__port_c__pin_a_for_encoder(3));
    mask |= (1U << keyboard__pins__port_c__pin_b_for_encoder(3));
    return mask;
}


uint8_t keyboard__pins__port_c__pins_mask(void) {
    return keyboard__pins__port_c__button_pins_mask() | keyboard__pins__port_c__encoders_pins_mask();
}
