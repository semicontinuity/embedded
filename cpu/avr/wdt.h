// =============================================================================
// WDT
// =============================================================================

#ifndef __CPU__AVR__WDT_H
#define __CPU__AVR__WDT_H

#include <avr/io.h>
#include <avr/wdt.h>

#if defined(__AVR_ATmega48__) ||\
    defined(__AVR_ATmega88__) ||\
    defined(__AVR_ATmega168__) ||\
    defined(__AVR_ATmega328P__)


inline void wdt__disable_unsafe(void) {
    __asm__ __volatile__ (                              \
        "sts %0, %1"            "\n\t"                  \
        "sts %0, __zero_reg__"  "\n\t"                  \
        : /* no outputs */                              \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)),         \
        "r" ((uint8_t)(_BV(_WD_CHANGE_BIT) | _BV(WDE))) \
    );
}


/**
 * Enable WDT.
 * Time-sensitive code, run with interrupts disabled.
 */
inline void wdt__enable_unsafe(const uint8_t value) {
    __asm__ __volatile__ (                                     \
        "sts %0, %1" "\n\t"                                    \
        "sts %0, %2" "\n\t"                                    \
        : /* no outputs */                                     \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)),                \
        "r" ((uint8_t)(_BV(_WD_CHANGE_BIT) | _BV(WDE))),       \
        "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | \
            _BV(WDE) | (value & 0x07)) )                       \
    );
}

/**
 * @param value one of WDTO_* constants.
 */
inline void wdt__prescaler_set(const uint8_t value) {
    __asm__ __volatile__ (                                                      \
        "sts %0, %1" "\n\t"                                                     \
        "sts %0, %2" "\n\t"                                                     \
        : /* no outputs */                                                      \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)),                                 \
        "r" ((uint8_t)(_BV(_WD_CHANGE_BIT) | _BV(WDE))),                        \
        "r" ((uint8_t) ((value & 0x08 ? _WD_PS3_MASK : 0x00) | (value & 0x07))) \
    );
}


inline void wdt__enable_interrupt(void) {
    __asm__ __volatile__ (                      \
        "sts %0, %1" "\n\t"                     \
        : /* no outputs */                      \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" ((uint8_t)(_BV(WDIE)))              \
    );
}

inline void wdt__disable_interrupt(void) {
    __asm__ __volatile__ (                      \
        "sts %0, %1" "\n\t"                     \
        : /* no outputs */                      \
        : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)), \
        "r" (0)                                 \
    );
}


#elif defined(__AVR_ATmega16__)


/**
 * Enable WDT.
 * @param value one of WDTO_* constants.
 */
inline void wdt__enable_unsafe(const uint8_t value) {
    __asm__ __volatile__ (                      \
    "out %0, %1" "\n\t"                         \
    : /* no outputs */                          \
    : "M" (_SFR_MEM_ADDR(_WD_CONTROL_REG)),     \
    "r" ((uint8_t)(_BV(WDE) | (value & 0x07)))  \
    );
}

#endif


inline void wdt__reset(void) {
    __asm__ __volatile__ ("wdr");
}

#endif
