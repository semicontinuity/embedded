#ifndef __DRIVERS__IO_MATRIX__IN_H
#define __DRIVERS__IO_MATRIX__IN_H

#include <stdint.h>

void io_matrix__in__init(void);

void io_matrix__in__column0__state__update(void);
uint8_t io_matrix__in__column0__state__get(void);

void io_matrix__in__column1__state__update(void);
uint8_t io_matrix__in__column1__state__get(void);

void io_matrix__in__column2__state__update(void);
uint8_t io_matrix__in__column2__state__get(void);

void io_matrix__in__column3__state__update(void);
uint8_t io_matrix__in__column3__state__get(void);

#endif