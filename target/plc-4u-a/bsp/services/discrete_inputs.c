#include <stdint.h>
#include "services/discrete_inputs.h"
#include "drivers/in/digital_inputs.h"

#include "drivers/in/buttons.h"
#include "drivers/in/extra_inputs.h"
#include "drivers/in/valve_limit_switches.h"
#include "drivers/in/water_leak_sensors.h"

#include "cpu/avr/asm.h"


#ifndef DEBOUNCE_TIMEOUT_MS
#define DEBOUNCE_TIMEOUT_MS (50)
#endif

#ifndef discrete_inputs__byte0
uint8_t discrete_inputs__byte0;
#endif

#ifndef discrete_inputs__byte1
uint8_t discrete_inputs__byte1;
#endif

int8_t discrete_inputs_debouncer__timeouts[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


bool discrete_inputs__0__get(void) {
    return discrete_inputs__byte0 & _BV(0);
}

bool discrete_inputs__1__get(void) {
    return discrete_inputs__byte0 & _BV(1);
}

bool discrete_inputs__2__get(void) {
    return discrete_inputs__byte0 & _BV(2);
}

bool discrete_inputs__3__get(void) {
    return discrete_inputs__byte0 & _BV(3);
}

bool discrete_inputs__4__get(void) {
    return discrete_inputs__byte0 & _BV(4);
}

bool discrete_inputs__5__get(void) {
    return discrete_inputs__byte0 & _BV(5);
}

bool discrete_inputs__6__get(void) {
    return discrete_inputs__byte0 & _BV(6);
}

bool discrete_inputs__7__get(void) {
    return discrete_inputs__byte0 & _BV(7);
}

bool discrete_inputs__8__get(void) {
    return discrete_inputs__byte1 & _BV(0);
}

bool discrete_inputs__9__get(void) {
    return discrete_inputs__byte1 & _BV(1);
}

bool discrete_inputs__a__get(void) {
    return discrete_inputs__byte1 & _BV(2);
}

bool discrete_inputs__b__get(void) {
    return discrete_inputs__byte1 & _BV(3);
}

bool discrete_inputs__c__get(void) {
    return discrete_inputs__byte1 & _BV(4);
}

bool discrete_inputs__d__get(void) {
    return discrete_inputs__byte1 & _BV(5);
}

bool discrete_inputs__e__get(void) {
    return discrete_inputs__byte1 & _BV(6);
}

bool discrete_inputs__f__get(void) {
    return discrete_inputs__byte1 & _BV(7);
}


inline __attribute__((always_inline)) bool discrete_inputs__get(uint8_t input) {
    if (input == 0x00) return discrete_inputs__0__get();
    if (input == 0x01) return discrete_inputs__1__get();
    if (input == 0x02) return discrete_inputs__2__get();
    if (input == 0x03) return discrete_inputs__3__get();
    if (input == 0x04) return discrete_inputs__4__get();
    if (input == 0x05) return discrete_inputs__5__get();
    if (input == 0x06) return discrete_inputs__6__get();
    if (input == 0x07) return discrete_inputs__7__get();
    if (input == 0x08) return discrete_inputs__8__get();
    if (input == 0x09) return discrete_inputs__9__get();
    if (input == 0x0A) return discrete_inputs__a__get();
    if (input == 0x0B) return discrete_inputs__b__get();
    if (input == 0x0C) return discrete_inputs__c__get();
    if (input == 0x0D) return discrete_inputs__d__get();
    if (input == 0x0E) return discrete_inputs__e__get();
    if (input == 0x0F) return discrete_inputs__f__get();
    return false;
}


/**
 * Implementation notes:
 * - Unrolled code for speed and easy lookup in *.lss listing.
 * - Using FIX_POINTER(timeouts) + direct index addressing; efficient, because uses LDD+STD instructions (offsets up to 64 bytes).
 * - Checkeng for changed bit is hard, easier to compute 8 changed bits with XOR.
 * - Could place COPY_BIT under if (changed), but not doing it: COPY_BIT is just 2 instructions,
 *   adding "if" would just add overhead without any gains.
 */
void discrete_inputs__run(void) {
    int8_t *timeouts = discrete_inputs_debouncer__timeouts;
    FIX_POINTER(timeouts);
    int8_t timeout;
    uint8_t bounced;
    uint8_t debounced;
    uint8_t changed;

    __asm__ __volatile__("discrete_inputs__debouncer__run__byte_0:");
    LOAD_CONST8(bounced, 0xFF);
    if (IS_1(DIGITAL_INPUTS__0)) bounced &= ~_BV(0);
    if (IS_1(DIGITAL_INPUTS__1)) bounced &= ~_BV(1);
    if (IS_1(DIGITAL_INPUTS__2)) bounced &= ~_BV(2);
    if (IS_1(DIGITAL_INPUTS__3)) bounced &= ~_BV(3);
    if (IS_1(DIGITAL_INPUTS__4)) bounced &= ~_BV(4);
    if (IS_1(DIGITAL_INPUTS__5)) bounced &= ~_BV(5);
    if (IS_1(DIGITAL_INPUTS__6)) bounced &= ~_BV(6);
    if (IS_1(DIGITAL_INPUTS__7)) bounced &= ~_BV(7);
    debounced = discrete_inputs__byte0;
    changed = bounced ^ debounced;


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_0:");
    timeout = timeouts[0x00];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 0, debounced, 0);
#ifdef discrete_inputs__on_input_0_changed
            if (changed & _BV(0)) {
                discrete_inputs__on_input_0_changed();
            }
#endif
        }
        timeouts[0x00] = timeout;
    } else {
        if (changed & _BV(0)) {
            timeouts[0x00] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_1:");
    timeout = timeouts[0x01];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 1, debounced, 1);
#ifdef discrete_inputs__on_input_1_changed
            if (changed & _BV(1)) {
                discrete_inputs__on_input_1_changed();
            }
#endif
        }
        timeouts[0x01] = timeout;
    } else {
        if (changed & _BV(1)) {
            timeouts[0x01] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_2:");
    timeout = timeouts[0x02];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 2, debounced, 2);
#ifdef discrete_inputs__on_input_2_changed
            if (changed & _BV(2)) {
                discrete_inputs__on_input_2_changed();
            }
#endif
        }
        timeouts[0x02] = timeout;
    } else {
        if (changed & _BV(2)) {
            timeouts[0x02] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_3:");
    timeout = timeouts[0x03];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 3, debounced, 3);
#ifdef discrete_inputs__on_input_3_changed
            if (changed & _BV(3)) {
                discrete_inputs__on_input_3_changed();
            }
#endif
        }
        timeouts[0x03] = timeout;
    } else {
        if (changed & _BV(3)) {
            timeouts[0x03] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_4:");
    timeout = timeouts[0x04];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 4, debounced, 4);
#ifdef discrete_inputs__on_input_4_changed
            if (changed & _BV(4)) {
                discrete_inputs__on_input_4_changed();
            }
#endif
        }
        timeouts[0x04] = timeout;
    } else {
        if (changed & _BV(4)) {
            timeouts[0x04] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_5:");
    timeout = timeouts[0x05];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 5, debounced, 5);
#ifdef discrete_inputs__on_input_5_changed
            if (changed & _BV(5)) {
                discrete_inputs__on_input_5_changed();
            }
#endif
        }
        timeouts[0x05] = timeout;
    } else {
        if (changed & _BV(5)) {
            timeouts[0x05] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_6:");
    timeout = timeouts[0x06];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 6, debounced, 6);
#ifdef discrete_inputs__on_input_6_changed
            if (changed & _BV(6)) {
                discrete_inputs__on_input_6_changed();
            }
#endif
        }
        timeouts[0x06] = timeout;
    } else {
        if (changed & _BV(6)) {
            timeouts[0x06] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_0_7:");
    timeout = timeouts[0x07];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 7, debounced, 7);
#ifdef discrete_inputs__on_input_7_changed
            if (changed & _BV(7)) {
                discrete_inputs__on_input_7_changed();
            }
#endif
        }
        timeouts[0x07] = timeout;
    } else {
        if (changed & _BV(7)) {
            timeouts[0x07] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__byte_0__done:");
    discrete_inputs__byte0 = debounced;


    __asm__ __volatile__("discrete_inputs__debouncer__run__byte_1:");
    LOAD_CONST8(bounced, 0xFF);
    if (extra_input__a__get()) bounced &= ~_BV(0);
    if (extra_input__b__get()) bounced &= ~_BV(1);
    if (button__a__get()) bounced &= ~_BV(2);
    if (button__b__get()) bounced &= ~_BV(3);
    if (button__c__get()) bounced &= ~_BV(4);
    if (button__d__get()) bounced &= ~_BV(5);
    if (button__e__get()) bounced &= ~_BV(6);
    if (button__f__get()) bounced &= ~_BV(7);
    debounced = discrete_inputs__byte1;
    changed = bounced ^ debounced;


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_0:");
    timeout = timeouts[0x08];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 0, debounced, 0);
#ifdef discrete_inputs__on_input_8_changed
            if (changed & _BV(0)) {
                discrete_inputs__on_input_8_changed();
            }
#endif
        }
        timeouts[0x08] = timeout;
    } else {
        if (changed & _BV(0)) {
            timeouts[0x08] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_1:");
    timeout = timeouts[0x09];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 1, debounced, 1);
#ifdef discrete_inputs__on_input_9_changed
            if (changed & _BV(1)) {
                discrete_inputs__on_input_9_changed();
            }
#endif
        }
        timeouts[0x09] = timeout;
    } else {
        if (changed & _BV(1)) {
            timeouts[0x09] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_2:");
    timeout = timeouts[0x0A];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 2, debounced, 2);
#ifdef discrete_inputs__on_input_a_changed
            if (changed & _BV(2)) {
                discrete_inputs__on_input_a_changed();
            }
#endif
        }
        timeouts[0x0A] = timeout;
    } else {
        if (changed & _BV(2)) {
            timeouts[0x0A] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_3:");
    timeout = timeouts[0x0B];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 3, debounced, 3);
#ifdef discrete_inputs__on_input_b_changed
            if (changed & _BV(3)) {
                discrete_inputs__on_input_b_changed();
            }
#endif
        }
        timeouts[0x0B] = timeout;
    } else {
        if (changed & _BV(3)) {
            timeouts[0x0B] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_4:");
    timeout = timeouts[0x0C];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 4, debounced, 4);
#ifdef discrete_inputs__on_input_c_changed
            if (changed & _BV(4)) {
                discrete_inputs__on_input_c_changed();
            }
#endif
        }
        timeouts[0x0C] = timeout;
    } else {
        if (changed & _BV(4)) {
            timeouts[0x0C] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_5:");
    timeout = timeouts[0x0D];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 5, debounced, 5);
#ifdef discrete_inputs__on_input_d_changed
            if (changed & _BV(5)) {
                discrete_inputs__on_input_d_changed();
            }
#endif
        }
        timeouts[0x0D] = timeout;
    } else {
        if (changed & _BV(5)) {
            timeouts[0x0D] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_6:");
    timeout = timeouts[0x0E];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 6, debounced, 6);
#ifdef discrete_inputs__on_input_e_changed
            if (changed & _BV(6)) {
                discrete_inputs__on_input_e_changed();
            }
#endif
        }
        timeouts[0x0E] = timeout;
    } else {
        if (changed & _BV(6)) {
            timeouts[0x0E] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__bit_1_7:");
    timeout = timeouts[0x0F];
    if (--timeout >= 0) {
        if (timeout == 0) {
            COPY_BIT(bounced, 7, debounced, 7);
#ifdef discrete_inputs__on_input_f_changed
            if (changed & _BV(7)) {
                discrete_inputs__on_input_f_changed();
            }
#endif
        }
        timeouts[0x0F] = timeout;
    } else {
        if (changed & _BV(7)) {
            timeouts[0x0F] = DEBOUNCE_TIMEOUT_MS;
        }
    }


    __asm__ __volatile__("discrete_inputs__debouncer__run__byte_1__done:");
    discrete_inputs__byte1 = debounced;
}
