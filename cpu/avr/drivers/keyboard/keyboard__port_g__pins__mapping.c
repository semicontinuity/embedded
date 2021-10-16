#include "cpu/avr/drivers/keyboard/keyboard__port_g__pins__mapping.h"

/**
 * Provides pin number for the given button (if it pertains to port G)
 * @param button 32-63 for BUTTON32..BUTTON63
*/
uint8_t keyboard__pins__port_g__pin_for_button(const uint8_t button) {
#if defined(IN__BUTTON32__PORT) && defined(IN__BUTTON32__PIN)
#if SINGLEQUOTED(IN__BUTTON32__PORT) == 'G'
    if (button == 32) return IN__BUTTON32__PIN;
#endif
#endif

#if defined(IN__BUTTON33__PORT) && defined(IN__BUTTON33__PIN)
#if SINGLEQUOTED(IN__BUTTON33__PORT) == 'G'
    if (button == 33) return IN__BUTTON33__PIN;
#endif
#endif

#if defined(IN__BUTTON34__PORT) && defined(IN__BUTTON34__PIN)
#if SINGLEQUOTED(IN__BUTTON34__PORT) == 'G'
    if (button == 34) return IN__BUTTON34__PIN;
#endif
#endif

#if defined(IN__BUTTON35__PORT) && defined(IN__BUTTON35__PIN)
#if SINGLEQUOTED(IN__BUTTON35__PORT) == 'G'
    if (button == 35) return IN__BUTTON35__PIN;
#endif
#endif

#if defined(IN__BUTTON36__PORT) && defined(IN__BUTTON36__PIN)
#if SINGLEQUOTED(IN__BUTTON36__PORT) == 'G'
    if (button == 36) return IN__BUTTON36__PIN;
#endif
#endif

#if defined(IN__BUTTON37__PORT) && defined(IN__BUTTON37__PIN)
#if SINGLEQUOTED(IN__BUTTON37__PORT) == 'G'
    if (button == 37) return IN__BUTTON37__PIN;
#endif
#endif

#if defined(IN__BUTTON38__PORT) && defined(IN__BUTTON38__PIN)
#if SINGLEQUOTED(IN__BUTTON38__PORT) == 'G'
    if (button == 38) return IN__BUTTON38__PIN;
#endif
#endif

#if defined(IN__BUTTON39__PORT) && defined(IN__BUTTON39__PIN)
#if SINGLEQUOTED(IN__BUTTON39__PORT) == 'G'
    if (button == 39) return IN__BUTTON39__PIN;
#endif
#endif

#if defined(IN__BUTTON40__PORT) && defined(IN__BUTTON40__PIN)
#if SINGLEQUOTED(IN__BUTTON40__PORT) == 'G'
    if (button == 40) return IN__BUTTON40__PIN;
#endif
#endif

#if defined(IN__BUTTON41__PORT) && defined(IN__BUTTON41__PIN)
#if SINGLEQUOTED(IN__BUTTON41__PORT) == 'G'
    if (button == 41) return IN__BUTTON41__PIN;
#endif
#endif

#if defined(IN__BUTTON42__PORT) && defined(IN__BUTTON42__PIN)
#if SINGLEQUOTED(IN__BUTTON42__PORT) == 'G'
    if (button == 42) return IN__BUTTON42__PIN;
#endif
#endif

#if defined(IN__BUTTON43__PORT) && defined(IN__BUTTON43__PIN)
#if SINGLEQUOTED(IN__BUTTON43__PORT) == 'G'
    if (button == 43) return IN__BUTTON43__PIN;
#endif
#endif

#if defined(IN__BUTTON44__PORT) && defined(IN__BUTTON44__PIN)
#if SINGLEQUOTED(IN__BUTTON44__PORT) == 'G'
    if (button == 44) return IN__BUTTON44__PIN;
#endif
#endif

#if defined(IN__BUTTON45__PORT) && defined(IN__BUTTON45__PIN)
#if SINGLEQUOTED(IN__BUTTON45__PORT) == 'G'
    if (button == 45) return IN__BUTTON45__PIN;
#endif
#endif

#if defined(IN__BUTTON46__PORT) && defined(IN__BUTTON46__PIN)
#if SINGLEQUOTED(IN__BUTTON46__PORT) == 'G'
    if (button == 46) return IN__BUTTON46__PIN;
#endif
#endif

#if defined(IN__BUTTON47__PORT) && defined(IN__BUTTON47__PIN)
#if SINGLEQUOTED(IN__BUTTON47__PORT) == 'G'
    if (button == 47) return IN__BUTTON47__PIN;
#endif
#endif

#if defined(IN__BUTTON48__PORT) && defined(IN__BUTTON48__PIN)
#if SINGLEQUOTED(IN__BUTTON48__PORT) == 'G'
    if (button == 48) return IN__BUTTON48__PIN;
#endif
#endif

#if defined(IN__BUTTON49__PORT) && defined(IN__BUTTON49__PIN)
#if SINGLEQUOTED(IN__BUTTON49__PORT) == 'G'
    if (button == 49) return IN__BUTTON49__PIN;
#endif
#endif

#if defined(IN__BUTTON50__PORT) && defined(IN__BUTTON50__PIN)
#if SINGLEQUOTED(IN__BUTTON50__PORT) == 'G'
    if (button == 50) return IN__BUTTON50__PIN;
#endif
#endif

#if defined(IN__BUTTON51__PORT) && defined(IN__BUTTON51__PIN)
#if SINGLEQUOTED(IN__BUTTON51__PORT) == 'G'
    if (button == 51) return IN__BUTTON51__PIN;
#endif
#endif

#if defined(IN__BUTTON52__PORT) && defined(IN__BUTTON52__PIN)
#if SINGLEQUOTED(IN__BUTTON52__PORT) == 'G'
    if (button == 52) return IN__BUTTON52__PIN;
#endif
#endif

#if defined(IN__BUTTON53__PORT) && defined(IN__BUTTON53__PIN)
#if SINGLEQUOTED(IN__BUTTON53__PORT) == 'G'
    if (button == 53) return IN__BUTTON53__PIN;
#endif
#endif

#if defined(IN__BUTTON54__PORT) && defined(IN__BUTTON54__PIN)
#if SINGLEQUOTED(IN__BUTTON54__PORT) == 'G'
    if (button == 54) return IN__BUTTON54__PIN;
#endif
#endif

#if defined(IN__BUTTON55__PORT) && defined(IN__BUTTON55__PIN)
#if SINGLEQUOTED(IN__BUTTON55__PORT) == 'G'
    if (button == 55) return IN__BUTTON55__PIN;
#endif
#endif

#if defined(IN__BUTTON56__PORT) && defined(IN__BUTTON56__PIN)
#if SINGLEQUOTED(IN__BUTTON56__PORT) == 'G'
    if (button == 56) return IN__BUTTON56__PIN;
#endif
#endif

#if defined(IN__BUTTON57__PORT) && defined(IN__BUTTON57__PIN)
#if SINGLEQUOTED(IN__BUTTON57__PORT) == 'G'
    if (button == 57) return IN__BUTTON57__PIN;
#endif
#endif

#if defined(IN__BUTTON58__PORT) && defined(IN__BUTTON58__PIN)
#if SINGLEQUOTED(IN__BUTTON58__PORT) == 'G'
    if (button == 58) return IN__BUTTON58__PIN;
#endif
#endif

#if defined(IN__BUTTON59__PORT) && defined(IN__BUTTON59__PIN)
#if SINGLEQUOTED(IN__BUTTON59__PORT) == 'G'
    if (button == 59) return IN__BUTTON59__PIN;
#endif
#endif

#if defined(IN__BUTTON60__PORT) && defined(IN__BUTTON60__PIN)
#if SINGLEQUOTED(IN__BUTTON60__PORT) == 'G'
    if (button == 60) return IN__BUTTON60__PIN;
#endif
#endif

#if defined(IN__BUTTON61__PORT) && defined(IN__BUTTON61__PIN)
#if SINGLEQUOTED(IN__BUTTON61__PORT) == 'G'
    if (button == 61) return IN__BUTTON61__PIN;
#endif
#endif

#if defined(IN__BUTTON62__PORT) && defined(IN__BUTTON62__PIN)
#if SINGLEQUOTED(IN__BUTTON62__PORT) == 'G'
    if (button == 62) return IN__BUTTON62__PIN;
#endif
#endif

#if defined(IN__BUTTON63__PORT) && defined(IN__BUTTON63__PIN)
#if SINGLEQUOTED(IN__BUTTON63__PORT) == 'G'
    if (button == 63) return IN__BUTTON63__PIN;
#endif
#endif

    return 0xFF;
}


uint8_t keyboard__pins__port_g__button_pins_mask(void) {
    uint8_t mask = 0;

#if defined(IN__BUTTON32__PORT) && defined(IN__BUTTON32__PIN)
#if SINGLEQUOTED(IN__BUTTON32__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON32__PIN));
#endif
#endif

#if defined(IN__BUTTON33__PORT) && defined(IN__BUTTON33__PIN)
#if SINGLEQUOTED(IN__BUTTON33__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON33__PIN));
#endif
#endif

#if defined(IN__BUTTON34__PORT) && defined(IN__BUTTON34__PIN)
#if SINGLEQUOTED(IN__BUTTON34__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON34__PIN));
#endif
#endif

#if defined(IN__BUTTON35__PORT) && defined(IN__BUTTON35__PIN)
#if SINGLEQUOTED(IN__BUTTON35__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON35__PIN));
#endif
#endif

#if defined(IN__BUTTON36__PORT) && defined(IN__BUTTON36__PIN)
#if SINGLEQUOTED(IN__BUTTON36__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON36__PIN));
#endif
#endif

#if defined(IN__BUTTON37__PORT) && defined(IN__BUTTON37__PIN)
#if SINGLEQUOTED(IN__BUTTON37__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON37__PIN));
#endif
#endif

#if defined(IN__BUTTON38__PORT) && defined(IN__BUTTON38__PIN)
#if SINGLEQUOTED(IN__BUTTON38__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON38__PIN));
#endif
#endif

#if defined(IN__BUTTON39__PORT) && defined(IN__BUTTON39__PIN)
#if SINGLEQUOTED(IN__BUTTON39__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON39__PIN));
#endif
#endif

#if defined(IN__BUTTON40__PORT) && defined(IN__BUTTON40__PIN)
#if SINGLEQUOTED(IN__BUTTON40__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON40__PIN));
#endif
#endif

#if defined(IN__BUTTON41__PORT) && defined(IN__BUTTON41__PIN)
#if SINGLEQUOTED(IN__BUTTON41__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON41__PIN));
#endif
#endif

#if defined(IN__BUTTON42__PORT) && defined(IN__BUTTON42__PIN)
#if SINGLEQUOTED(IN__BUTTON42__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON42__PIN));
#endif
#endif

#if defined(IN__BUTTON43__PORT) && defined(IN__BUTTON43__PIN)
#if SINGLEQUOTED(IN__BUTTON43__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON43__PIN));
#endif
#endif

#if defined(IN__BUTTON44__PORT) && defined(IN__BUTTON44__PIN)
#if SINGLEQUOTED(IN__BUTTON44__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON44__PIN));
#endif
#endif

#if defined(IN__BUTTON45__PORT) && defined(IN__BUTTON45__PIN)
#if SINGLEQUOTED(IN__BUTTON45__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON45__PIN));
#endif
#endif

#if defined(IN__BUTTON46__PORT) && defined(IN__BUTTON46__PIN)
#if SINGLEQUOTED(IN__BUTTON46__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON46__PIN));
#endif
#endif

#if defined(IN__BUTTON47__PORT) && defined(IN__BUTTON47__PIN)
#if SINGLEQUOTED(IN__BUTTON47__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON47__PIN));
#endif
#endif

#if defined(IN__BUTTON48__PORT) && defined(IN__BUTTON48__PIN)
#if SINGLEQUOTED(IN__BUTTON48__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON48__PIN));
#endif
#endif

#if defined(IN__BUTTON49__PORT) && defined(IN__BUTTON49__PIN)
#if SINGLEQUOTED(IN__BUTTON49__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON49__PIN));
#endif
#endif

#if defined(IN__BUTTON50__PORT) && defined(IN__BUTTON50__PIN)
#if SINGLEQUOTED(IN__BUTTON50__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON50__PIN));
#endif
#endif

#if defined(IN__BUTTON51__PORT) && defined(IN__BUTTON51__PIN)
#if SINGLEQUOTED(IN__BUTTON51__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON51__PIN));
#endif
#endif

#if defined(IN__BUTTON52__PORT) && defined(IN__BUTTON52__PIN)
#if SINGLEQUOTED(IN__BUTTON52__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON52__PIN));
#endif
#endif

#if defined(IN__BUTTON53__PORT) && defined(IN__BUTTON53__PIN)
#if SINGLEQUOTED(IN__BUTTON53__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON53__PIN));
#endif
#endif

#if defined(IN__BUTTON54__PORT) && defined(IN__BUTTON54__PIN)
#if SINGLEQUOTED(IN__BUTTON54__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON54__PIN));
#endif
#endif

#if defined(IN__BUTTON55__PORT) && defined(IN__BUTTON55__PIN)
#if SINGLEQUOTED(IN__BUTTON55__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON55__PIN));
#endif
#endif

#if defined(IN__BUTTON56__PORT) && defined(IN__BUTTON56__PIN)
#if SINGLEQUOTED(IN__BUTTON56__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON56__PIN));
#endif
#endif

#if defined(IN__BUTTON57__PORT) && defined(IN__BUTTON57__PIN)
#if SINGLEQUOTED(IN__BUTTON57__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON57__PIN));
#endif
#endif

#if defined(IN__BUTTON58__PORT) && defined(IN__BUTTON58__PIN)
#if SINGLEQUOTED(IN__BUTTON58__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON58__PIN));
#endif
#endif

#if defined(IN__BUTTON59__PORT) && defined(IN__BUTTON59__PIN)
#if SINGLEQUOTED(IN__BUTTON59__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON59__PIN));
#endif
#endif

#if defined(IN__BUTTON60__PORT) && defined(IN__BUTTON60__PIN)
#if SINGLEQUOTED(IN__BUTTON60__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON60__PIN));
#endif
#endif

#if defined(IN__BUTTON61__PORT) && defined(IN__BUTTON61__PIN)
#if SINGLEQUOTED(IN__BUTTON61__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON61__PIN));
#endif
#endif

#if defined(IN__BUTTON62__PORT) && defined(IN__BUTTON62__PIN)
#if SINGLEQUOTED(IN__BUTTON62__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON62__PIN));
#endif
#endif

#if defined(IN__BUTTON63__PORT) && defined(IN__BUTTON63__PIN)
#if SINGLEQUOTED(IN__BUTTON63__PORT) == 'G'
    mask |= (1U << (uint8_t)(IN__BUTTON63__PIN));
#endif
#endif

    return mask;
}


/**
 * Provides pin number for the given encoder A pin (if it pertains to port G)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_g__pin_a_for_encoder(const uint8_t encoder) {
#if defined(IN__ENCODER0__A__PORT) && defined(IN__ENCODER0__A__PIN)
#if SINGLEQUOTED(IN__ENCODER0__A__PORT) == 'G'
    if (encoder == 0) return IN__ENCODER0__A__PIN;
#endif
#endif

#if defined(IN__ENCODER1__A__PORT) && defined(IN__ENCODER1__A__PIN)
#if SINGLEQUOTED(IN__ENCODER1__A__PORT) == 'G'
    if (encoder == 1) return IN__ENCODER1__A__PIN;
#endif
#endif

#if defined(IN__ENCODER2__A__PORT) && defined(IN__ENCODER2__A__PIN)
#if SINGLEQUOTED(IN__ENCODER2__A__PORT) == 'G'
    if (encoder == 2) return IN__ENCODER2__A__PIN;
#endif
#endif

#if defined(IN__ENCODER3__A__PORT) && defined(IN__ENCODER3__A__PIN)
#if SINGLEQUOTED(IN__ENCODER3__A__PORT) == 'G'
    if (encoder == 3) return IN__ENCODER3__A__PIN;
#endif
#endif

    return 0xFF;
}


/**
 * Provides pin number for the given encoder B pin (if it pertains to port G)
 * @param encoder 0-3 for ENCODER0..ENCODER3
*/
uint8_t keyboard__pins__port_g__pin_b_for_encoder(const uint8_t encoder) {
#if defined(IN__ENCODER0__B__PORT) && defined(IN__ENCODER0__B__PIN)
#if SINGLEQUOTED(IN__ENCODER0__B__PORT) == 'G'
    if (encoder == 0) return IN__ENCODER0__B__PIN;
#endif
#endif

#if defined(IN__ENCODER1__B__PORT) && defined(IN__ENCODER1__B__PIN)
#if SINGLEQUOTED(IN__ENCODER1__B__PORT) == 'G'
    if (encoder == 1) return IN__ENCODER1__B__PIN;
#endif
#endif

#if defined(IN__ENCODER2__B__PORT) && defined(IN__ENCODER2__B__PIN)
#if SINGLEQUOTED(IN__ENCODER2__B__PORT) == 'G'
    if (encoder == 2) return IN__ENCODER2__B__PIN;
#endif
#endif

#if defined(IN__ENCODER3__B__PORT) && defined(IN__ENCODER3__B__PIN)
#if SINGLEQUOTED(IN__ENCODER3__B__PORT) == 'G'
    if (encoder == 3) return IN__ENCODER3__B__PIN;
#endif
#endif

    return 0xFF;
}


uint8_t keyboard__pins__port_g__encoders_pins_mask(void) {
    uint8_t mask = 0;
    mask |= (1U << keyboard__pins__port_g__pin_a_for_encoder(0));
    mask |= (1U << keyboard__pins__port_g__pin_b_for_encoder(0));
    mask |= (1U << keyboard__pins__port_g__pin_a_for_encoder(1));
    mask |= (1U << keyboard__pins__port_g__pin_b_for_encoder(1));
    mask |= (1U << keyboard__pins__port_g__pin_a_for_encoder(2));
    mask |= (1U << keyboard__pins__port_g__pin_b_for_encoder(2));
    mask |= (1U << keyboard__pins__port_g__pin_a_for_encoder(3));
    mask |= (1U << keyboard__pins__port_g__pin_b_for_encoder(3));
    return mask;
}


uint8_t keyboard__pins__port_g__pins_mask(void) {
    return keyboard__pins__port_g__button_pins_mask() | keyboard__pins__port_g__encoders_pins_mask();
}
