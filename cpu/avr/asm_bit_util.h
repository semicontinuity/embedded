#ifndef __CPU__AVR__ASM_BIT_UTIL_H
#define __CPU__AVR__ASM_BIT_UTIL_H

#include <cpu/avr/macros.h>
#include <cpu/avr/asm.h>
#include <stdint.h>


uint16_t interlace_bits(uint8_t sl, uint8_t sh) {
    uint8_t rl, rh;
    rl = __builtin_avr_insert_bits(
            avr_insert_bits_map(
                    8,
                    8,
                    8,
                    8,
                    6,
                    4,
                    2,
                    0
                    ),
                    sl,
                    0
                    );
    rl = __builtin_avr_insert_bits(
            avr_insert_bits_map(
                    6,
                    4,
                    2,
                    0,
                    0xFF,
                    0xFF,
                    0xFF,
                    0xFF
                    ),
                    sh,
                    rl
                    );

    rh = __builtin_avr_insert_bits(
            avr_insert_bits_map(
                    1,
                    3,
                    5,
                    7,
                    8,
                    8,
                    8,
                    8
                    ),
                    sl,
                    0
                    );
    rh = __builtin_avr_insert_bits(
            avr_insert_bits_map(
                    0x0f,
                    0x0f,
                    0x0f,
                    0x0f,
                    1,
                    3,
                    5,
                    7
                    ),
                    sh,
                    rh
                    );

    return (rh << 8U) | (rl & 0xFFU);
}


uint8_t interlace_bits_l(uint8_t sl, uint8_t sh) {
    uint8_t rl;
    COPY_BIT(sl, 0, rl, 0);
    COPY_BIT(sl, 2, rl, 1);
    COPY_BIT(sl, 4, rl, 2);
    COPY_BIT(sl, 6, rl, 3);
    COPY_BIT(sh, 0, rl, 4);
    COPY_BIT(sh, 2, rl, 5);
    COPY_BIT(sh, 4, rl, 6);
    COPY_BIT(sh, 6, rl, 7);
    return rl;
}

uint8_t interlace_bits_h(uint8_t sl, uint8_t sh) {
    uint8_t rh;
    COPY_BIT(sl, 1, rh, 0);
    COPY_BIT(sl, 3, rh, 1);
    COPY_BIT(sl, 5, rh, 2);
    COPY_BIT(sl, 7, rh, 3);
    COPY_BIT(sh, 1, rh, 4);
    COPY_BIT(sh, 3, rh, 5);
    COPY_BIT(sh, 5, rh, 6);
    COPY_BIT(sh, 6, rh, 7);
    return rh;
}

#endif