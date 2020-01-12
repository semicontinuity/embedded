// =============================================================================
// Hardware-abstracted driver for MT12232-type display.
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12232_HAL__MT12232_HAL_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12232_HAL__MT12232_HAL_H

#include <stdint.h>


/** Initialize display */
void mt12232_hal__init(void);

/** Copy a part of page (8-pixel-high strip) from RAM to LCD memory */
void mt12232_hal__copy(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t* data);

/** Fill with mask a part of page (8-pixel-high strip) */
void mt12232_hal__fill_with(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t mask);

/** AND with mask a part of page (8-pixel-high strip) */
void mt12232_hal__and_with(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t mask);

/** OR with mask a part of page (8-pixel-high strip) */
void mt12232_hal__or_with(const uint8_t page, const uint8_t x_from, const uint8_t x_to, const uint8_t mask);


void mt12232_hal__blt_with_right_shift(
        const uint8_t page,
        const uint8_t x_from,
        const uint8_t x_to,
        const uint8_t shift,
        const uint8_t mask,
        const uint8_t set_bits_flag,
        volatile uint8_t *src);

void mt12232_hal__blt_with_left_shift(
        const uint8_t page,
        const uint8_t x_from,
        const uint8_t x_to,
        const uint8_t shift,
        const uint8_t mask,
        const uint8_t set_bits_flag,
        uint8_t *src);

#endif
