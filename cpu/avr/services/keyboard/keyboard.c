#include "cpu/avr/services/keyboard/keyboard.h"


#ifdef KEYBOARD__COMMON_MASK__REG


#include "cpu/avr/drivers/keyboard/keyboard__port_a__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_b__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_c__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_d__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_e__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_f__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_g__pins__mapping.h"
#include "cpu/avr/drivers/keyboard/keyboard__port_h__pins__mapping.h"


inline void keyboard__init_common_mask(void) {
    __asm__ __volatile__("keyboard__init_common_mask:");

    uint8_t common_mask = 0;

#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    common_mask |= keyboard__pins__port_a__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_a__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    common_mask |= keyboard__pins__port_b__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_b__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    common_mask |= keyboard__pins__port_c__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_c__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    common_mask |= keyboard__pins__port_d__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_d__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_E__USED) && KEYBOARD__PORT_E__USED == 1
    common_mask |= keyboard__pins__port_e__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_e__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1
    common_mask |= keyboard__pins__port_f__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_f__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1
    common_mask |= keyboard__pins__port_g__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_g__encoders_pins_mask();
#endif
#endif

#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1
    common_mask |= keyboard__pins__port_h__button_pins_mask();
#if defined(KEYBOARD__ENCODERS) && KEYBOARD__ENCODERS == 1
    common_mask |= keyboard__pins__port_h__encoders_pins_mask();
#endif
#endif

    keyboard__common_mask = common_mask;
}
#endif



inline void keyboard__init_masks(void) {
#ifdef KEYBOARD__COMMON_MASK__REG
    keyboard__init_common_mask();
#endif
    __asm__ __volatile__("keyboard__init_masks:");
    keyboard__reset_masks();
}



void keyboard__reset_masks(void) {
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__mask__reset();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__mask__reset();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__mask__reset();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__mask__reset();
#endif
#if defined(KEYBOARD__PORT_E__USED) && KEYBOARD__PORT_E__USED == 1
    keyboard__port_e__mask__reset();
#endif
#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1
    keyboard__port_f__mask__reset();
#endif
#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1
    keyboard__port_g__mask__reset();
#endif
#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1
    keyboard__port_h__mask__reset();
#endif
}


inline void keyboard__init_previous_states(void) {
    __asm__ __volatile__("keyboard__init_previous_states:");
#if defined(KEYBOARD__PORT_A__USED) && KEYBOARD__PORT_A__USED == 1
    keyboard__port_a__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_B__USED) && KEYBOARD__PORT_B__USED == 1
    keyboard__port_b__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_C__USED) && KEYBOARD__PORT_C__USED == 1
    keyboard__port_c__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_D__USED) && KEYBOARD__PORT_D__USED == 1
    keyboard__port_d__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_E__USED) && KEYBOARD__PORT_E__USED == 1
    keyboard__port_e__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1
    keyboard__port_f__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1
    keyboard__port_g__init_previous_state();
#endif
#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1
    keyboard__port_h__init_previous_state();
#endif
}



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
#if defined(KEYBOARD__PORT_E__USED) && KEYBOARD__PORT_E__USED == 1
    __asm__ __volatile__("keyboard__port_e__debounce_timer__init:");
    keyboard__port_e__debounce_timer__init();
#endif
#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1
    __asm__ __volatile__("keyboard__port_f__debounce_timer__init:");
    keyboard__port_f__debounce_timer__init();
#endif
#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1
    __asm__ __volatile__("keyboard__port_g__debounce_timer__init:");
    keyboard__port_g__debounce_timer__init();
#endif
#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1
    __asm__ __volatile__("keyboard__port_h__debounce_timer__init:");
    keyboard__port_h__debounce_timer__init();
#endif
}


void keyboard__init(void) {
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
#if defined(KEYBOARD__PORT_E__USED) && KEYBOARD__PORT_E__USED == 1
    keyboard__port_e__run();
#endif
#if defined(KEYBOARD__PORT_F__USED) && KEYBOARD__PORT_F__USED == 1
    keyboard__port_f__run();
#endif
#if defined(KEYBOARD__PORT_G__USED) && KEYBOARD__PORT_G__USED == 1
    keyboard__port_g__run();
#endif
#if defined(KEYBOARD__PORT_H__USED) && KEYBOARD__PORT_H__USED == 1
    keyboard__port_h__run();
#endif
}
