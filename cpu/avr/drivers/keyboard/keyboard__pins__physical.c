#include "cpu/avr/drivers/keyboard/keyboard__pins.h"
#include "cpu/avr/gpio.h"

void keyboard__pins__init(void) {
#if defined(IN__BUTTON0__PORT) && defined(IN__BUTTON0__PIN)
    USE_AS_INPUT(IN__BUTTON0);
    ENABLE_PULLUP(IN__BUTTON0);
#endif
#if defined(IN__BUTTON1__PORT) && defined(IN__BUTTON1__PIN)
    USE_AS_INPUT(IN__BUTTON1);
    ENABLE_PULLUP(IN__BUTTON1);
#endif
#if defined(IN__BUTTON2__PORT) && defined(IN__BUTTON2__PIN)
    USE_AS_INPUT(IN__BUTTON2);
    ENABLE_PULLUP(IN__BUTTON2);
#endif
#if defined(IN__BUTTON3__PORT) && defined(IN__BUTTON3__PIN)
    USE_AS_INPUT(IN__BUTTON3);
    ENABLE_PULLUP(IN__BUTTON3);
#endif

#if defined(IN__BUTTON4__PORT) && defined(IN__BUTTON4__PIN)
    USE_AS_INPUT(IN__BUTTON4);
    ENABLE_PULLUP(IN__BUTTON4);
#endif
#if defined(IN__BUTTON5__PORT) && defined(IN__BUTTON5__PIN)
    USE_AS_INPUT(IN__BUTTON5);
    ENABLE_PULLUP(IN__BUTTON5);
#endif
#if defined(IN__BUTTON6__PORT) && defined(IN__BUTTON6__PIN)
    USE_AS_INPUT(IN__BUTTON6);
    ENABLE_PULLUP(IN__BUTTON6);
#endif
#if defined(IN__BUTTON7__PORT) && defined(IN__BUTTON7__PIN)
    USE_AS_INPUT(IN__BUTTON7);
    ENABLE_PULLUP(IN__BUTTON7);
#endif

#if defined(IN__BUTTON8__PORT) && defined(IN__BUTTON8__PIN)
    USE_AS_INPUT(IN__BUTTON8);
    ENABLE_PULLUP(IN__BUTTON8);
#endif
#if defined(IN__BUTTON9__PORT) && defined(IN__BUTTON9__PIN)
    USE_AS_INPUT(IN__BUTTON9);
    ENABLE_PULLUP(IN__BUTTON9);
#endif
#if defined(IN__BUTTON10__PORT) && defined(IN__BUTTON10__PIN)
    USE_AS_INPUT(IN__BUTTON10);
    ENABLE_PULLUP(IN__BUTTON10);
#endif
#if defined(IN__BUTTON11__PORT) && defined(IN__BUTTON11__PIN)
    USE_AS_INPUT(IN__BUTTON11);
    ENABLE_PULLUP(IN__BUTTON11);
#endif

#if defined(IN__BUTTON12__PORT) && defined(IN__BUTTON12__PIN)
    USE_AS_INPUT(IN__BUTTON12);
    ENABLE_PULLUP(IN__BUTTON12);
#endif
#if defined(IN__BUTTON13__PORT) && defined(IN__BUTTON13__PIN)
    USE_AS_INPUT(IN__BUTTON13);
    ENABLE_PULLUP(IN__BUTTON13);
#endif
#if defined(IN__BUTTON14__PORT) && defined(IN__BUTTON14__PIN)
    USE_AS_INPUT(IN__BUTTON14);
    ENABLE_PULLUP(IN__BUTTON14);
#endif
#if defined(IN__BUTTON15__PORT) && defined(IN__BUTTON15__PIN)
    USE_AS_INPUT(IN__BUTTON15);
    ENABLE_PULLUP(IN__BUTTON15);
#endif

#if defined(IN__BUTTON16__PORT) && defined(IN__BUTTON16__PIN)
    USE_AS_INPUT(IN__BUTTON16);
    ENABLE_PULLUP(IN__BUTTON16);
#endif
#if defined(IN__BUTTON17__PORT) && defined(IN__BUTTON17__PIN)
    USE_AS_INPUT(IN__BUTTON17);
    ENABLE_PULLUP(IN__BUTTON17);
#endif
#if defined(IN__BUTTON18__PORT) && defined(IN__BUTTON18__PIN)
    USE_AS_INPUT(IN__BUTTON18);
    ENABLE_PULLUP(IN__BUTTON18);
#endif
#if defined(IN__BUTTON19__PORT) && defined(IN__BUTTON19__PIN)
    USE_AS_INPUT(IN__BUTTON19);
    ENABLE_PULLUP(IN__BUTTON19);
#endif
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
