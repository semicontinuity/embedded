#ifndef KEYBOARD__PINS_H
#define KEYBOARD__PINS_H


void keyboard__pins__init(void);


#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
uint8_t keyboard__pins__port_a__read(void);
#endif

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
uint8_t keyboard__pins__port_b__read(void);
#endif

#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
uint8_t keyboard__pins__port_c__read(void);
#endif

#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
uint8_t keyboard__pins__port_d__read(void);
#endif

#endif
