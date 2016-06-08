// =============================================================================
// Soft SPI 1 driver.
// =============================================================================

#ifndef __SOFT_SPI1_H
#define __SOFT_SPI1_H

#include <stdint.h>

void soft_spi1__init(void);

void soft_spi1__write(uint8_t value);

#endif