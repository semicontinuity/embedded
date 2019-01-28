// =============================================================================
// Soft SPI 0 driver.
// =============================================================================

#ifndef __SOFT_SPI0_H
#define __SOFT_SPI0_H

#include <stdint.h>

void soft_spi0__init(void);

void soft_spi0__write(uint8_t value);

#endif