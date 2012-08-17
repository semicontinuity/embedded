#ifndef __IN_PWD_ENTERED__H
#define __IN_PWD_ENTERED__H

#include "cpu/avr/gpio.h"
#include <stdbool.h>


static inline void pwd_entered__init(void) {}


static inline bool pwd_entered__is_active(void) {
    return IS_0(PWD_ENTERED);
}

static inline bool pwd_entered__run(void) {
    // TODO: interrupt
    static uint8_t pwd_pulse = 0;
    if (pwd_entered__is_active()) {
        if (!pwd_pulse) {
            pwd_pulse = 1;
            pwd_entered__on_active();
            
        }
    }
    else {
          /* It is faster just to set pwd_pulse to 0 unconditionally */
//        if (pwd_pulse)
//        {
            pwd_pulse = 0;
//        }
    }
}

void pwd_entered__on_active(void);


#endif