// =============================================================================
// Hardware-abstracted driver for MT12232-type display.
// =============================================================================
#ifndef __CPU__AVR__DRIVERS__DISPLAY__MT12232_HAL__MT12232_HAL_H
#define __CPU__AVR__DRIVERS__DISPLAY__MT12232_HAL__MT12232_HAL_H

#include <stdint.h>


/** Initialize display */
void mt12232_hal__init(void);

/** Copy a part of page (8-pixel-high strip) from RAM to LCD memory */
void mt12232_hal__send_strip(const uint8_t* data, const uint8_t page, const uint8_t x_from, const uint8_t x_to);

#endif
