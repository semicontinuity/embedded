#include "cpu/avr/drivers/keyboard/keyboard__pins__mapping.h"


/**
 * Provides pin number for the given button (if it pertains to port B)
 * @param button 0-31 for BUTTON0..BUTTON31
*/
uint8_t keyboard__pins__port_b__pin_for_button(const uint8_t button) {
#if defined(IN__BUTTON0__PORT) && defined(IN__BUTTON0__PIN)
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xB
    if (button == 0) return IN__BUTTON0__PIN;
#endif
#endif

#if defined(IN__BUTTON1__PORT) && defined(IN__BUTTON1__PIN)
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xB
    if (button == 1) return IN__BUTTON1__PIN;
#endif
#endif

#if defined(IN__BUTTON2__PORT) && defined(IN__BUTTON2__PIN)
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xB
    if (button == 2) return IN__BUTTON2__PIN;
#endif
#endif

#if defined(IN__BUTTON3__PORT) && defined(IN__BUTTON3__PIN)
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xB
    if (button == 3) return IN__BUTTON3__PIN;
#endif
#endif

#if defined(IN__BUTTON4__PORT) && defined(IN__BUTTON4__PIN)
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xB
    if (button == 4) return IN__BUTTON4__PIN;
#endif
#endif

#if defined(IN__BUTTON5__PORT) && defined(IN__BUTTON5__PIN)
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xB
    if (button == 5) return IN__BUTTON5__PIN;
#endif
#endif

#if defined(IN__BUTTON6__PORT) && defined(IN__BUTTON6__PIN)
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xB
    if (button == 6) return IN__BUTTON6__PIN;
#endif
#endif

#if defined(IN__BUTTON7__PORT) && defined(IN__BUTTON7__PIN)
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xB
    if (button == 7) return IN__BUTTON7__PIN;
#endif
#endif

#if defined(IN__BUTTON8__PORT) && defined(IN__BUTTON8__PIN)
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xB
    if (button == 8) return IN__BUTTON8__PIN;
#endif
#endif

#if defined(IN__BUTTON9__PORT) && defined(IN__BUTTON9__PIN)
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xB
    if (button == 9) return IN__BUTTON9__PIN;
#endif
#endif

#if defined(IN__BUTTON10__PORT) && defined(IN__BUTTON10__PIN)
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xB
    if (button == 10) return IN__BUTTON10__PIN;
#endif
#endif

#if defined(IN__BUTTON11__PORT) && defined(IN__BUTTON11__PIN)
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xB
    if (button == 11) return IN__BUTTON11__PIN;
#endif
#endif

#if defined(IN__BUTTON12__PORT) && defined(IN__BUTTON12__PIN)
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xB
    if (button == 12) return IN__BUTTON12__PIN;
#endif
#endif

#if defined(IN__BUTTON13__PORT) && defined(IN__BUTTON13__PIN)
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xB
    if (button == 13) return IN__BUTTON13__PIN;
#endif
#endif

#if defined(IN__BUTTON14__PORT) && defined(IN__BUTTON14__PIN)
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xB
    if (button == 14) return IN__BUTTON14__PIN;
#endif
#endif

#if defined(IN__BUTTON15__PORT) && defined(IN__BUTTON15__PIN)
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xB
    if (button == 15) return IN__BUTTON15__PIN;
#endif
#endif

#if defined(IN__BUTTON16__PORT) && defined(IN__BUTTON16__PIN)
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xB
    if (button == 16) return IN__BUTTON16__PIN;
#endif
#endif

#if defined(IN__BUTTON17__PORT) && defined(IN__BUTTON17__PIN)
#if CONCAT(0x, IN__BUTTON17__PORT) == 0xB
    if (button == 17) return IN__BUTTON17__PIN;
#endif
#endif

#if defined(IN__BUTTON18__PORT) && defined(IN__BUTTON18__PIN)
#if CONCAT(0x, IN__BUTTON18__PORT) == 0xB
    if (button == 18) return IN__BUTTON18__PIN;
#endif
#endif

#if defined(IN__BUTTON19__PORT) && defined(IN__BUTTON19__PIN)
#if CONCAT(0x, IN__BUTTON19__PORT) == 0xB
    if (button == 19) return IN__BUTTON19__PIN;
#endif
#endif

    return 0xFF;
}


uint8_t keyboard__pins__port_b__button_pins_mask(void) {
    uint8_t mask = 0;

#if defined(IN__BUTTON0__PORT) && defined(IN__BUTTON0__PIN)
#if CONCAT(0x, IN__BUTTON0__PORT) == 0xB
    mask |= (1 << (IN__BUTTON0__PIN));
#endif
#endif

#if defined(IN__BUTTON1__PORT) && defined(IN__BUTTON1__PIN)
#if CONCAT(0x, IN__BUTTON1__PORT) == 0xB
    mask |= (1 << (IN__BUTTON1__PIN));
#endif
#endif

#if defined(IN__BUTTON2__PORT) && defined(IN__BUTTON2__PIN)
#if CONCAT(0x, IN__BUTTON2__PORT) == 0xB
    mask |= (1 << (IN__BUTTON2__PIN));
#endif
#endif

#if defined(IN__BUTTON3__PORT) && defined(IN__BUTTON3__PIN)
#if CONCAT(0x, IN__BUTTON3__PORT) == 0xB
    mask |= (1 << (IN__BUTTON3__PIN));
#endif
#endif

#if defined(IN__BUTTON4__PORT) && defined(IN__BUTTON4__PIN)
#if CONCAT(0x, IN__BUTTON4__PORT) == 0xB
    mask |= (1 << (IN__BUTTON4__PIN));
#endif
#endif

#if defined(IN__BUTTON5__PORT) && defined(IN__BUTTON5__PIN)
#if CONCAT(0x, IN__BUTTON5__PORT) == 0xB
    mask |= (1 << (IN__BUTTON5__PIN));
#endif
#endif

#if defined(IN__BUTTON6__PORT) && defined(IN__BUTTON6__PIN)
#if CONCAT(0x, IN__BUTTON6__PORT) == 0xB
    mask |= (1 << (IN__BUTTON6__PIN));
#endif
#endif

#if defined(IN__BUTTON7__PORT) && defined(IN__BUTTON7__PIN)
#if CONCAT(0x, IN__BUTTON7__PORT) == 0xB
    mask |= (1 << (IN__BUTTON7__PIN));
#endif
#endif

#if defined(IN__BUTTON8__PORT) && defined(IN__BUTTON8__PIN)
#if CONCAT(0x, IN__BUTTON8__PORT) == 0xB
    mask |= (1 << (IN__BUTTON8__PIN));
#endif
#endif

#if defined(IN__BUTTON9__PORT) && defined(IN__BUTTON9__PIN)
#if CONCAT(0x, IN__BUTTON9__PORT) == 0xB
    mask |= (1 << (IN__BUTTON9__PIN));
#endif
#endif

#if defined(IN__BUTTON10__PORT) && defined(IN__BUTTON10__PIN)
#if CONCAT(0x, IN__BUTTON10__PORT) == 0xB
    mask |= (1 << (IN__BUTTON10__PIN));
#endif
#endif

#if defined(IN__BUTTON11__PORT) && defined(IN__BUTTON11__PIN)
#if CONCAT(0x, IN__BUTTON11__PORT) == 0xB
    mask |= (1 << (IN__BUTTON11__PIN));
#endif
#endif

#if defined(IN__BUTTON12__PORT) && defined(IN__BUTTON12__PIN)
#if CONCAT(0x, IN__BUTTON12__PORT) == 0xB
    mask |= (1 << (IN__BUTTON12__PIN));
#endif
#endif

#if defined(IN__BUTTON13__PORT) && defined(IN__BUTTON13__PIN)
#if CONCAT(0x, IN__BUTTON13__PORT) == 0xB
    mask |= (1 << (IN__BUTTON13__PIN));
#endif
#endif

#if defined(IN__BUTTON14__PORT) && defined(IN__BUTTON14__PIN)
#if CONCAT(0x, IN__BUTTON14__PORT) == 0xB
    mask |= (1 << (IN__BUTTON14__PIN));
#endif
#endif

#if defined(IN__BUTTON15__PORT) && defined(IN__BUTTON15__PIN)
#if CONCAT(0x, IN__BUTTON15__PORT) == 0xB
    mask |= (1 << (IN__BUTTON15__PIN));
#endif
#endif

#if defined(IN__BUTTON16__PORT) && defined(IN__BUTTON16__PIN)
#if CONCAT(0x, IN__BUTTON16__PORT) == 0xB
    mask |= (1 << (IN__BUTTON16__PIN));
#endif
#endif

#if defined(IN__BUTTON17__PORT) && defined(IN__BUTTON17__PIN)
#if CONCAT(0x, IN__BUTTON17__PORT) == 0xB
    mask |= (1 << (IN__BUTTON17__PIN));
#endif
#endif

#if defined(IN__BUTTON18__PORT) && defined(IN__BUTTON18__PIN)
#if CONCAT(0x, IN__BUTTON18__PORT) == 0xB
    mask |= (1 << (IN__BUTTON18__PIN));
#endif
#endif

#if defined(IN__BUTTON19__PORT) && defined(IN__BUTTON19__PIN)
#if CONCAT(0x, IN__BUTTON19__PORT) == 0xB
    mask |= (1 << (IN__BUTTON19__PIN));
#endif
#endif

    return mask;
}
