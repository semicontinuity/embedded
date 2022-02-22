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

#define INTERLACE_BITS_L(l, h)                              \
(__extension__({                                            \
    uint8_t __result;                                       \
    __asm__ __volatile__(                                   \
    "bst  %1, 0\r\n"                                        \
    "bld  %0, 0\r\n"                                        \
    "bst  %1, 2\r\n"                                        \
    "bld  %0, 1\r\n"                                        \
    "bst  %1, 4\r\n"                                        \
    "bld  %0, 2\r\n"                                        \
    "bst  %1, 6\r\n"                                        \
    "bld  %0, 3\r\n"                                        \
    "bst  %2, 0\r\n"                                        \
    "bld  %0, 4\r\n"                                        \
    "bst  %2, 2\r\n"                                        \
    "bld  %0, 5\r\n"                                        \
    "bst  %2, 4\r\n"                                        \
    "bld  %0, 6\r\n"                                        \
    "bst  %2, 6\r\n"                                        \
    "bld  %0, 7\r\n"                                        \
    : "=&r"(__result)                                        \
    : "r"((l)), "r"((h))                                    \
    );                                                      \
    __result;                                               \
}))


uint8_t interlace_bits_l0(uint8_t rl, uint8_t sl, uint8_t sh) {
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


#define INTERLACE_BITS_H(l, h)                              \
(__extension__({                                            \
    uint8_t __result;                                       \
    __asm__ __volatile__(                                   \
    "bst  %1, 1\r\n"                                        \
    "bld  %0, 0\r\n"                                        \
    "bst  %1, 3\r\n"                                        \
    "bld  %0, 1\r\n"                                        \
    "bst  %1, 5\r\n"                                        \
    "bld  %0, 2\r\n"                                        \
    "bst  %1, 7\r\n"                                        \
    "bld  %0, 3\r\n"                                        \
    "bst  %2, 1\r\n"                                        \
    "bld  %0, 4\r\n"                                        \
    "bst  %2, 3\r\n"                                        \
    "bld  %0, 5\r\n"                                        \
    "bst  %2, 5\r\n"                                        \
    "bld  %0, 6\r\n"                                        \
    "bst  %2, 7\r\n"                                        \
    "bld  %0, 7\r\n"                                        \
    : "=&r"(__result)                                        \
    : "r"((l)), "r"((h))                                    \
    );                                                      \
    __result;                                               \
}))


uint8_t interlace_bits_h0(uint8_t rh, uint8_t sl, uint8_t sh) {
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