#ifndef __SERVICES__CONSOLE_I2C_H
#define __SERVICES__CONSOLE_I2C_H

#include <stdint.h>

void console__i2c__init(void);

uint8_t console__i2c__run(void);

#endif